#include "httpcpp/HttpClient.hpp"
#include "httpcpp/HttpResponse.hpp"
#include "httpcpp/Socket.hpp"
#include <exception>
#include <iostream>

int main()
{
    try
    {
        httpcpp::Socket socket;
        httpcpp::HttpClient client(&socket);
        httpcpp::HttpResponse const response
            = client.get("http://www.google.com");

        std::cout << "Status Code: " << response.getStatusCode() << '\n';
        std::cout << "Headers:" << '\n';
        for (const auto& header : response.getHeaders()) {
            std::cout << "  " << header.first << ": " << header.second << '\n';
        }
        std::cout << "Body:" << '\n';
        std::cout << response.getBody() << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
