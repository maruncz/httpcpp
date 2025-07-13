#include "httpcpp/Socket.hpp"
#include <asm-generic/socket.h>
#include <boost/ut.hpp>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <vector>

namespace
{

// Simple echo server to run in a separate thread
void echo_server(uint16_t port, bool& running)
{
    int const server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1)
    {
        perror("socket failed");
        return;
    }

    int opt = 1;

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))
        != 0)
    {
        perror("setsockopt");
        return;
    }

    struct sockaddr_in address
    {
    };
    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        return;
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        return;
    }

    running = true;

    int addrlen = sizeof(address);

    int const new_socket
        = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    if (new_socket < 0)
    {
        perror("accept");
        return;
    }

    char buffer[1024]     = {0};
    ssize_t const valread = read(new_socket, buffer, 1024);
    send(new_socket, buffer, valread, 0);

    close(new_socket);
    close(server_fd);
}

} // namespace

int main()
{
    using namespace boost::ut;

    "SocketTest"_test = []
    {
        uint16_t const port = 8081;
        bool server_running = false;
        std::thread server_thread(echo_server, port, std::ref(server_running));

        // Give the server a moment to start
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        expect(that % server_running);

        httpcpp::Socket client_socket;
        client_socket.connect("127.0.0.1", port);

        std::string message = "Hello, World!";
        std::vector<uint8_t> const request_data(message.begin(), message.end());
        client_socket.send(request_data);

        std::vector<uint8_t> response_data = client_socket.receive(1024);
        std::string response_message(response_data.begin(),
                                     response_data.end());

        expect(message == response_message);

        client_socket.close();
        server_thread.join();
    };
}
