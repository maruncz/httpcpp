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
    HttpResponse get(const std::string& url);
    HttpResponse post(const std::string& url, const std::string& body);

private:
    ISocket* socket_ {nullptr};
};

} // namespace httpcpp
