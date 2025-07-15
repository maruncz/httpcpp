#pragma once

#include "HttpResponse.hpp"
#include "ISocket.hpp"
#include <string>

namespace httpcpp
{

class HttpClient
{
public:
    explicit HttpClient(ISocket* socket) : socket_(socket) {}
    HttpResponse get(const std::string& url,
                     const std::map<std::string, std::string>& headers = {});
    HttpResponse post(const std::string& url, const std::string& body,
                      const std::map<std::string, std::string>& headers = {});

private:
    ISocket* socket_ {nullptr};
};

} // namespace httpcpp
