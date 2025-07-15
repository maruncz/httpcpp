#pragma once

#include "HttpResponse.hpp"
#include "ISocket.hpp"
#include <cstdint>
#include <map>
#include <string>

namespace httpcpp
{

class HttpClient
{
    struct ParsedUrl
    {
        std::string host;
        uint16_t port = 0;
        std::string path;
        int error_code = 0;
    };

public:
    explicit HttpClient(ISocket* socket) : socket_(socket) {}
    HttpResponse get(const std::string& url,
                     const std::map<std::string, std::string>& headers = {});
    HttpResponse post(const std::string& url, const std::string& body,
                      const std::map<std::string, std::string>& headers = {});

private:
    [[nodiscard]] static ParsedUrl parseUrl(std::string url);

    ISocket* socket_ {nullptr};
};

} // namespace httpcpp
