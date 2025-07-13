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

private:
    Socket socket_;
};

} // namespace httpcpp
