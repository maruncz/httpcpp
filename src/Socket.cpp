#include "httpcpp/Socket.hpp"
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <netdb.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

namespace httpcpp
{


Socket::~Socket()
{
    if (sock_ != -1)
    {
        ::close(sock_);
    }
}

void Socket::connect(const std::string& host, uint16_t port)
{
    std::array<char, 6> port_str {};
    (void)snprintf(port_str.data(), port_str.size(), "%d", port);

    struct addrinfo hints {};
    std::memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family   = AF_UNSPEC; /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = 0;
    hints.ai_protocol = 0;

    struct addrinfo* result {nullptr};
    int const s = getaddrinfo(host.c_str(), port_str.data(), &hints, &result);
    if (s != 0)
    {
        throw std::runtime_error(std::string("getaddrinfo: ")
                                 + gai_strerror(s));
    }

    struct addrinfo* rp {nullptr};
    for (rp = result; rp != nullptr; rp = rp->ai_next)
    {
        sock_ = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sock_ == -1)
        {
            continue;
        }

        if (::connect(sock_, rp->ai_addr, rp->ai_addrlen) != -1)
        {
            break; /* Success */
        }

        ::close(sock_);
        sock_ = -1;
    }

    freeaddrinfo(result); /* No longer needed */

    if (rp == nullptr)
    { /* No address succeeded */
        throw std::runtime_error("Could not connect");
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
    ssize_t const bytes_received = ::recv(sock_, buffer.data(), max_size, 0);
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
