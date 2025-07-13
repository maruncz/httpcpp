#pragma once

#include "HttpResponse.hpp"
#include <string>

namespace httpcpp
{

class HttpResponseParser
{
public:
    HttpResponse parse(const std::string& rawResponse);
};

} // namespace httpcpp
