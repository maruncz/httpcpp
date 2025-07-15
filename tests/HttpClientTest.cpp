#include "httpcpp/HttpClient.hpp"
#include "httpcpp/HttpResponse.hpp"
#include "httpcpp/ISocket.hpp"
#include <boost/ut.hpp>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

// NOLINTBEGIN(readability-magic-numbers)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

class MockSocket : public httpcpp::ISocket
{
public:
    void connect(const std::string& host, uint16_t port) override
    {
        host_ = host;
        port_ = port;
    }

    void send(const std::vector<uint8_t>& data) override { sent_data_ = data; }

    std::vector<uint8_t> receive(size_t /*max_size*/) override
    {
        std::string response
            = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nHello";
        return {response.begin(), response.end()};
    }

    void close() override { closed_ = true; }

    std::string host_;
    uint16_t port_ = 0;
    std::vector<uint8_t> sent_data_;
    bool closed_ = false;
};

int main()
{
    using namespace boost::ut;

    "HttpClientGet"_test = []
    {
        MockSocket mock_socket;
        httpcpp::HttpClient client(&mock_socket);

        httpcpp::HttpResponse const response
            = client.get("http://example.com/path");

        expect(that % std::string("example.com") == mock_socket.host_);
        expect(that % 80 == mock_socket.port_);

        std::string expected_request
            = "GET /path HTTP/1.1\r\nHost: example.com\r\n\r\n";
        std::vector<uint8_t> const expected_request_data(
            expected_request.begin(), expected_request.end());
        expect(that % expected_request_data == mock_socket.sent_data_);

        expect(that % 200 == response.getStatusCode());
        expect(that % std::string("5")
               == response.getHeaders().at("Content-Length"));
        expect(that % 5 == response.getBody().length());
        expect(that % std::string("Hello") == response.getBody());
    };

    "HttpClientGetWithHttps"_test = []
    {
        MockSocket mock_socket;
        httpcpp::HttpClient client(&mock_socket);

        expect(throws<std::runtime_error>(
            [&] { client.get("https://example.com/path"); }));
    };

    "HttpClientGetWithPort"_test = []
    {
        MockSocket mock_socket;
        httpcpp::HttpClient client(&mock_socket);

        httpcpp::HttpResponse const response
            = client.get("http://example.com:8080/path");

        expect(that % std::string("example.com") == mock_socket.host_);
        expect(that % 8080 == mock_socket.port_);

        std::string expected_request
            = "GET /path HTTP/1.1\r\nHost: example.com\r\n\r\n";
        std::vector<uint8_t> const expected_request_data(
            expected_request.begin(), expected_request.end());
        expect(that % expected_request_data == mock_socket.sent_data_);

        expect(that % 200 == response.getStatusCode());
        expect(that % std::string("5")
               == response.getHeaders().at("Content-Length"));
        expect(that % 5 == response.getBody().length());
        expect(that % std::string("Hello") == response.getBody());
    };

    "HttpClientPostWithHeaders"_test = []
    {
        MockSocket mock_socket;
        httpcpp::HttpClient client(&mock_socket);

        std::string const post_body = "key=value";
        httpcpp::HttpResponse const response
            = client.post("http://example.com/resource", post_body,
                          {
                              {"Authorization",     "Bearer token"},
                              {       "Accept", "application/json"}
        });

        expect(that % std::string("example.com") == mock_socket.host_);
        expect(that % 80 == mock_socket.port_);

        std::string expected_request
            = "POST /resource HTTP/1.1\r\nHost: "
              "example.com\r\nAccept: application/json\r\nAuthorization: "
              "Bearer token\r\nContent-Length: 9\r\n\r\nkey=value";
        std::vector<uint8_t> const expected_request_data(
            expected_request.begin(), expected_request.end());
        expect(that % expected_request_data == mock_socket.sent_data_);

        expect(that % 200 == response.getStatusCode());
        expect(that % std::string("Hello") == response.getBody());
    };
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(readability-magic-numbers)
