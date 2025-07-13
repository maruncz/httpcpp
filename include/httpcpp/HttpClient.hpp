#pragma once

#include "Socket.hpp"
#include "HttpResponse.hpp"
#include <string>
#include <vector>

namespace httpcpp
{

class HttpClient
{
public:
    HttpClient();
    HttpResponse get(const std::string& url);

private:
    Socket socket_;
};

} // namespace httpcpp
