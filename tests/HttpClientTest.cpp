#include "httpcpp/HttpClient.hpp"
#include "httpcpp/HttpResponse.hpp"
#include <boost/ut.hpp>

int main()
{
    using namespace boost::ut;

    "PostRequest"_test = []
    {
        httpcpp::HttpClient client;
        httpcpp::HttpResponse response
            = client.post("http://httpbin.org/post", "key=value");

        expect(200_i == response.getStatusCode());
        expect(response.getBody().find("\"data\": \"key=value\"")
               != std::string::npos);
    };
}
