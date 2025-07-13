#include "httpcpp/HttpResponseParser.hpp"
#include "httpcpp/HttpResponse.hpp"
#include <cstddef>
#include <sstream>
#include <string>

namespace httpcpp
{

HttpResponse HttpResponseParser::parse(const std::string& rawResponse)
{
    HttpResponse response;
    std::stringstream ss(rawResponse);
    std::string line;

    // Parse status line
    std::getline(ss, line);
    if (line.starts_with("HTTP/1.1 "))
    {
        response.setStatusCode(std::stoi(line.substr(9, 3)));
    }

    // Parse headers
    while (std::getline(ss, line) && line != "\r")
    {
        size_t const colon_pos = line.find(':');
        if (colon_pos != std::string::npos) {
            std::string const name  = line.substr(0, colon_pos);
            std::string const value = line.substr(colon_pos + 2); // Skip ": "
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
