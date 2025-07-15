#include "httpcpp/HttpClient.hpp"
#include "httpcpp/HttpResponse.hpp"
#include "httpcpp/HttpResponseParser.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace httpcpp
{

HttpResponse HttpClient::get(const std::string& url,
                             const std::map<std::string, std::string>& headers)
{
    auto const parsed_url = parseUrl(url);
    if (parsed_url.error_code != 0)
    {
        throw std::runtime_error("URL parsing failed.");
    }

    socket_->connect(parsed_url.host, parsed_url.port);

    std::string request = "GET " + parsed_url.path
                        + " HTTP/1.1\r\nHost: " + parsed_url.host + "\r\n";
    for (const auto& header : headers)
    {
        request += header.first + ": " + header.second + "\r\n";
    }
    request += "\r\n";
    std::vector<uint8_t> const request_data(request.begin(), request.end());
    socket_->send(request_data);

    std::vector<uint8_t> response_data = socket_->receive(4096);
    std::string const response_str(response_data.begin(), response_data.end());

    HttpResponseParser const parser;
    return HttpResponseParser::parse(response_str);
}

HttpResponse HttpClient::post(const std::string& url, const std::string& body,
                              const std::map<std::string, std::string>& headers)
{
    auto const parsed_url = parseUrl(url);
    if (parsed_url.error_code != 0)
    {
        throw std::runtime_error("URL parsing failed.");
    }

    socket_->connect(parsed_url.host, parsed_url.port);

    std::string request = "POST " + parsed_url.path
                        + " HTTP/1.1\r\nHost: " + parsed_url.host + "\r\n";
    for (const auto& header : headers)
    {
        request += header.first + ": " + header.second + "\r\n";
    }
    request += "Content-Length: " + std::to_string(body.length()) + "\r\n\r\n"
             + body;
    std::cout << "Request: " << request << '\n';
    std::vector<uint8_t> const request_data(request.begin(), request.end());
    socket_->send(request_data);

    std::vector<uint8_t> response_data = socket_->receive(4096);
    std::string const response_str(response_data.begin(), response_data.end());
    std::cout << "Response: " << response_str << '\n';

    HttpResponseParser const parser;
    return httpcpp::HttpResponseParser::parse(response_str);
}

HttpClient::ParsedUrl HttpClient::parseUrl(std::string url)
{
    ParsedUrl result;

    if (url.find("://") == std::string::npos)
    {
        url.insert(0, "http://");
    }

    if (url.starts_with("https://"))
    {
        result.error_code = 1;
        return result;
    }

    if (url.starts_with("http://"))
    {
        url = url.substr(7);
    }

    size_t const port_pos = url.find(':');
    size_t const path_pos = url.find('/');

    result.port = 80;

    if (port_pos != std::string::npos)
    {
        result.host = url.substr(0, port_pos);
        result.port
            = std::stoi(url.substr(port_pos + 1, path_pos - (port_pos + 1)));
    }
    else
    {
        result.host = url.substr(0, path_pos);
    }

    if (path_pos != std::string::npos)
    {
        result.path = url.substr(path_pos);
    }
    else
    {
        result.path = "/";
    }

    return result;
}

} // namespace httpcpp
