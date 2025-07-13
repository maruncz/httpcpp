#include <iostream>
#include "httpcpp/HttpClient.hpp"
#include "httpcpp/HttpResponse.hpp"

int main()
{
    try
    {
        httpcpp::HttpClient client;
        httpcpp::HttpResponse response = client.get("http://www.google.com");

        std::cout << "Status Code: " << response.getStatusCode() << std::endl;
        std::cout << "Headers:" << std::endl;
        for (const auto& header : response.getHeaders()) {
            std::cout << "  " << header.first << ": " << header.second << std::endl;
        }
        std::cout << "Body:" << std::endl;
        std::cout << response.getBody() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
