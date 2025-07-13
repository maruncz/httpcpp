#pragma once

#include <string>
#include <vector>
#include <map>

namespace httpcpp
{

class HttpResponse
{
public:
    int getStatusCode() const;
    void setStatusCode(int code);

    const std::map<std::string, std::string>& getHeaders() const;
    void addHeader(const std::string& name, const std::string& value);

    const std::string& getBody() const;
    void setBody(const std::string& body);

private:
    int statusCode_;
    std::map<std::string, std::string> headers_;
    std::string body_;
};

} // namespace httpcpp
