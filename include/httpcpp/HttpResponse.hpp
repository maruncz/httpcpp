#pragma once

#include <map>
#include <string>

namespace httpcpp
{

class HttpResponse
{
public:
    [[nodiscard]] int getStatusCode() const;
    void setStatusCode(int code);

    [[nodiscard]] const std::map<std::string, std::string>& getHeaders() const;
    void addHeader(const std::string& name, const std::string& value);

    [[nodiscard]] const std::string& getBody() const;
    void setBody(const std::string& body);

private:
    int statusCode_;
    std::map<std::string, std::string> headers_;
    std::string body_;
};

} // namespace httpcpp
