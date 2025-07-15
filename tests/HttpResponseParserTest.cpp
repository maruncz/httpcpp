#include "httpcpp/HttpResponseParser.hpp"
#include "httpcpp/HttpResponse.hpp"
#include <boost/ut.hpp>
#include <string>

// NOLINTBEGIN(readability-magic-numbers)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

int main()
{
    using namespace boost::ut;

    "ParseValidResponse"_test = []
    {
        httpcpp::HttpResponseParser const parser;
        std::string const rawResponse = "HTTP/1.1 200 OK\r\n"
                                        "Content-Type: text/html\r\n"
                                        "Content-Length: 13\r\n"
                                        "\r\n"
                                        "Hello, World!";
        httpcpp::HttpResponse const response
            = httpcpp::HttpResponseParser::parse(rawResponse);

        expect(200_i == response.getStatusCode());
        expect("text/html" == response.getHeaders().at("Content-Type"));
        expect("13" == response.getHeaders().at("Content-Length"));
        expect("Hello, World!" == response.getBody());
    };

    "ParseResponseWithNoTrailingNewlineInBody"_test = []
    {
        httpcpp::HttpResponseParser const parser;
        std::string const rawResponse = "HTTP/1.1 200 OK\r\n"
                                        "Content-Type: text/plain\r\n"
                                        "Content-Length: 4\r\n"
                                        "\r\n"
                                        "test";
        httpcpp::HttpResponse const response
            = httpcpp::HttpResponseParser::parse(rawResponse);

        expect(200_i == response.getStatusCode());
        expect("test" == response.getBody());
    };

    "ParseResponseWithNoBody"_test = []
    {
        httpcpp::HttpResponseParser const parser;
        std::string const rawResponse = "HTTP/1.1 204 No Content\r\n"
                                        "\r\n";
        httpcpp::HttpResponse const response
            = httpcpp::HttpResponseParser::parse(rawResponse);

        expect(204_i == response.getStatusCode());
        expect(response.getHeaders().empty());
        expect(response.getBody().empty());
    };
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(readability-magic-numbers)
