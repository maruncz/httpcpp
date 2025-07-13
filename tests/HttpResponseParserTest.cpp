#include <boost/ut.hpp>
#include "httpcpp/HttpResponseParser.hpp"

int main()
{
    using namespace boost::ut;

    "ParseValidResponse"_test = [] {
        httpcpp::HttpResponseParser parser;
        std::string rawResponse = "HTTP/1.1 200 OK\r\n"
                                  "Content-Type: text/html\r\n"
                                  "Content-Length: 13\r\n"
                                  "\r\n"
                                  "Hello, World!";
        httpcpp::HttpResponse response = parser.parse(rawResponse);

        expect(200_i == response.getStatusCode());
        expect("text/html" == response.getHeaders().at("Content-Type"));
        expect("13" == response.getHeaders().at("Content-Length"));
        expect("Hello, World!\n" == response.getBody());
    };

    "ParseResponseWithNoBody"_test = [] {
        httpcpp::HttpResponseParser parser;
        std::string rawResponse = "HTTP/1.1 204 No Content\r\n"
                                  "\r\n";
        httpcpp::HttpResponse response = parser.parse(rawResponse);

        expect(204_i == response.getStatusCode());
        expect(response.getHeaders().empty());
        expect(response.getBody().empty());
    };
}
