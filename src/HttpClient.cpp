#include "httpcpp/HttpClient.hpp"
#include "httpcpp/HttpResponse.hpp"
#include "httpcpp/HttpResponseParser.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace httpcpp
{

HttpResponse HttpClient::get(const std::string& url)
{
    // A simple URL parser to get host and path
    std::string temp_url = url;
    if (temp_url.starts_with("http://"))
    {
        temp_url = temp_url.substr(7);
    }

    size_t const path_pos  = temp_url.find('/');
    std::string const host = temp_url.substr(0, path_pos);
    std::string const path
        = (path_pos == std::string::npos) ? "/" : temp_url.substr(path_pos);

    socket_->connect(host, 80);

    std::string request
        = "GET " + path + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
    std::vector<uint8_t> const request_data(request.begin(), request.end());
    socket_->send(request_data);

    std::vector<uint8_t> response_data = socket_->receive(4096);
    std::string const response_str(response_data.begin(), response_data.end());

    HttpResponseParser const parser;
    return HttpResponseParser::parse(response_str);
}

HttpResponse HttpClient::post(const std::string& url, const std::string& body)
{
    std::string temp_url = url;
    if (temp_url.starts_with("http://"))
    {
        temp_url = temp_url.substr(7);
    }

    size_t const path_pos  = temp_url.find('/');
    std::string const host = temp_url.substr(0, path_pos);
    std::string const path
        = (path_pos == std::string::npos) ? "/" : temp_url.substr(path_pos);

    socket_->connect(host, 80);

    std::string request
        = "POST " + path + " HTTP/1.1\r\nHost: " + host
        + "\r\nUser-Agent: httpcpp/1.0\r\nContent-Type: "
          "application/x-www-form-urlencoded\r\nContent-Length: "
        + std::to_string(body.length()) + "\r\n\r\n" + body;
    std::cout << "Request: " << request << '\n';
    std::vector<uint8_t> const request_data(request.begin(), request.end());
    socket_->send(request_data);

    std::vector<uint8_t> response_data = socket_->receive(4096);
    std::string const response_str(response_data.begin(), response_data.end());
    std::cout << "Response: " << response_str << '\n';

    HttpResponseParser const parser;
    return httpcpp::HttpResponseParser::parse(response_str);
}

} // namespace httpcpp
