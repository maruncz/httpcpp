#include "httpcpp/HttpResponseParser.hpp"
#include <sstream>
#include <iostream>

namespace httpcpp
{

HttpResponse HttpResponseParser::parse(const std::string& rawResponse)
{
    HttpResponse response;
    std::stringstream ss(rawResponse);
    std::string line;

    // Parse status line
    std::getline(ss, line);
    if (line.rfind("HTTP/1.1 ", 0) == 0) {
        response.setStatusCode(std::stoi(line.substr(9, 3)));
    }

    // Parse headers
    while (std::getline(ss, line) && line != "\r") {
        size_t colon_pos = line.find(':');
        if (colon_pos != std::string::npos) {
            std::string name = line.substr(0, colon_pos);
            std::string value = line.substr(colon_pos + 2); // Skip ": "
            response.addHeader(name, value.substr(0, value.length() - 1)); // Remove \r
        }
    }

    // Parse body
    std::string body;
    std::string body_line;
    while (std::getline(ss, body_line)) {
        body += body_line + "\n";
    }
    response.setBody(body);

    return response;
}

} // namespace httpcpp
