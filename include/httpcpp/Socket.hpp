#pragma once

#include "ISocket.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace httpcpp
{

class Socket : public ISocket
{
public:

    Socket() = default;
    ~Socket() override;
    Socket(const Socket&o ) = delete;
    Socket(Socket&& o ) = delete;
    Socket& operator=(const Socket& o) = delete;
    Socket& operator=(Socket&& o) = delete;


    void connect(const std::string& host, uint16_t port) override;
    void send(const std::vector<uint8_t>& data) override;
    std::vector<uint8_t> receive(size_t max_size) override;
    void close() override;

private:
    int sock_{-1};
};

} // namespace httpcpp
