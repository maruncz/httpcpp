#include <iostream>
#include "httpcpp/HttpClient.hpp"

int main()
{
    try
    {
        httpcpp::HttpClient client;
        std::string response = client.get("http://www.google.com");
        std::cout << response << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
