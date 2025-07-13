#pragma once

#include "HttpResponse.hpp"
#include "Socket.hpp"
#include <string>

namespace httpcpp
{

class HttpClient
{
public:
    HttpResponse get(const std::string& url);
    HttpResponse post(const std::string& url, const std::string& body);

private:
    Socket socket_;
};

} // namespace httpcpp
