#include "gtest/gtest.h"
#include "httpcpp/HttpResponseParser.hpp"

TEST(HttpResponseParserTest, ParseValidResponse)
{
    httpcpp::HttpResponseParser parser;
    std::string rawResponse = "HTTP/1.1 200 OK\r\n"
                              "Content-Type: text/html\r\n"
                              "Content-Length: 13\r\n"
                              "\r\n"
                              "Hello, World!";
    httpcpp::HttpResponse response = parser.parse(rawResponse);

    ASSERT_EQ(200, response.getStatusCode());
    ASSERT_EQ("text/html", response.getHeaders().at("Content-Type"));
    ASSERT_EQ("13", response.getHeaders().at("Content-Length"));
    ASSERT_EQ("Hello, World!\n", response.getBody());
}

TEST(HttpResponseParserTest, ParseResponseWithNoBody)
{
    httpcpp::HttpResponseParser parser;
    std::string rawResponse = "HTTP/1.1 204 No Content\r\n"
                              "\r\n";
    httpcpp::HttpResponse response = parser.parse(rawResponse);

    ASSERT_EQ(204, response.getStatusCode());
    ASSERT_TRUE(response.getHeaders().empty());
    ASSERT_TRUE(response.getBody().empty());
}
