#pragma once
#include <iostream>
#include <boost/asio/buffer.hpp>

#include "MarketDepthMessage.hpp"

/**
 * Converts market data to internal data structure
 */
using mutable_buffers_type = boost::asio::mutable_buffer;
using string = std::string;

class MarketDataHandler {
private:

public:
    void consumeMarketData(MarketDepthMessage) {
    }
};