#include "httpcpp/Socket.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include <cstring>

namespace httpcpp
{

Socket::Socket() : sock_(-1)
{
}

Socket::~Socket()
{
    if (sock_ != -1)
    {
        ::close(sock_);
    }
}

void Socket::connect(const std::string& host, uint16_t port)
{
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ < 0)
    {
        throw std::runtime_error("Failed to create socket");
    }

    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &serv_addr.sin_addr) <= 0)
    {
        throw std::runtime_error("Invalid address/ Address not supported");
    }

    if (::connect(sock_, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        throw std::runtime_error("Connection Failed");
    }
}

void Socket::send(const std::vector<uint8_t>& data)
{
    if (::send(sock_, data.data(), data.size(), 0) < 0)
    {
        throw std::runtime_error("Send failed");
    }
}

std::vector<uint8_t> Socket::receive(size_t max_size)
{
    std::vector<uint8_t> buffer(max_size);
    ssize_t bytes_received = ::recv(sock_, buffer.data(), max_size, 0);
    if (bytes_received < 0)
    {
        throw std::runtime_error("Receive failed");
    }
    buffer.resize(bytes_received);
    return buffer;
}

void Socket::close()
{
    if (sock_ != -1)
    {
        ::close(sock_);
        sock_ = -1;
    }
}

} // namespace httpcpp
