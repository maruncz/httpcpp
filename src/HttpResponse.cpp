#include "httpcpp/HttpResponse.hpp"

namespace httpcpp
{

int HttpResponse::getStatusCode() const
{
    return statusCode_;
}

void HttpResponse::setStatusCode(int code)
{
    statusCode_ = code;
}

const std::map<std::string, std::string>& HttpResponse::getHeaders() const
{
    return headers_;
}

void HttpResponse::addHeader(const std::string& name, const std::string& value)
{
    headers_[name] = value;
}

const std::string& HttpResponse::getBody() const
{
    return body_;
}

void HttpResponse::setBody(const std::string& body)
{
    body_ = body;
}

} // namespace httpcpp
