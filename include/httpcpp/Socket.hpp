#pragma once

#include "ISocket.hpp"
#include <string>
#include <vector>
#include <cstdint>

namespace httpcpp
{

class Socket : public ISocket
{
public:
    Socket();
    ~Socket() override;

    void connect(const std::string& host, uint16_t port) override;
    void send(const std::vector<uint8_t>& data) override;
    std::vector<uint8_t> receive(size_t max_size) override;
    void close() override;

private:
    int sock_;
};

} // namespace httpcpp
