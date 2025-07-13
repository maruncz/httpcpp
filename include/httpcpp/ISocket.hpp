#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace httpcpp
{

class ISocket
{
public:
    virtual void connect(const std::string& host, uint16_t port) = 0;
    virtual void send(const std::vector<uint8_t>& data) = 0;
    virtual std::vector<uint8_t> receive(size_t max_size) = 0;
    virtual void close() = 0;

    ISocket() = default;
    virtual ~ISocket() = default;
    ISocket(const ISocket&o ) = delete;
    ISocket(ISocket&& o ) = delete;
    ISocket& operator=(const ISocket& o) = delete;
    ISocket& operator=(ISocket&& o) = delete;
};

} // namespace httpcpp
