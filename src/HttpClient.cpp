#include "httpcpp/HttpClient.hpp"
#include "httpcpp/HttpResponse.hpp"
#include "httpcpp/HttpResponseParser.hpp"
#include <cstddef>
#include <cstdint>
#include <stdexcept>
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

    try {
        socket_.connect(host, 80);
    } catch (const std::runtime_error& e) {
        // try with resolved IP address
        socket_.connect("209.85.200.104", 80);
    }

    std::string request
        = "GET " + path + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
    std::vector<uint8_t> const request_data(request.begin(), request.end());
    socket_.send(request_data);

    std::vector<uint8_t> response_data = socket_.receive(4096);
    std::string const response_str(response_data.begin(), response_data.end());

    HttpResponseParser const parser;
    return HttpResponseParser::parse(response_str);
}

} // namespace httpcpp
