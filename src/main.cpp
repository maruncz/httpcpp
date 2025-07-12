#include <iostream>
#include "httpcpp/Socket.hpp"
#include <vector>
#include <string>

int main()
{
    try
    {
        httpcpp::Socket socket;
        socket.connect("209.85.200.104", 80);

        std::string request = "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
        std::vector<uint8_t> request_data(request.begin(), request.end());
        socket.send(request_data);

        std::vector<uint8_t> response = socket.receive(4096);

        std::cout << std::string(response.begin(), response.end()) << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
