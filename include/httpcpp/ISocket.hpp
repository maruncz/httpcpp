#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace httpcpp
{

class ISocket
{
public:
    virtual ~ISocket() = default;

    virtual void connect(const std::string& host, uint16_t port) = 0;
    virtual void send(const std::vector<uint8_t>& data) = 0;
    virtual std::vector<uint8_t> receive(size_t max_size) = 0;
    virtual void close() = 0;
};

} // namespace httpcpp
