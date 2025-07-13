#pragma once

#include "httpcpp/ISocket.hpp"
#include <cstdint>
#include <string>
#include <vector>

class MockSocket : public httpcpp::ISocket
{
public:
    void connect(const std::string& host, uint16_t port) override {}
    void send(const std::vector<uint8_t>& data) override {}
    std::vector<uint8_t> receive(size_t max_size) override
    {
        std::vector<uint8_t> buffer(receive_buffer_.begin(),
                                    receive_buffer_.end());
        return buffer;
    }
    void close() override {}
    void setReceiveBuffer(const std::string& buffer) override
    {
        receive_buffer_ = buffer;
    }

private:
    std::string receive_buffer_;
};
