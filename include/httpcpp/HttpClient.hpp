#pragma once

#include "Socket.hpp"
#include <string>
#include <vector>

namespace httpcpp
{

class HttpClient
{
public:
    HttpClient();
    std::string get(const std::string& url);

private:
    Socket socket_;
};

} // namespace httpcpp
