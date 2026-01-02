#pragma once

#include "Order.hpp"
#include <vector>

class MarketDepthMessage {
    std::vector<Order> bids;
    std::vector<Order> asks;

    static std::vector<std::string> splitStringOnDelim(const std::string& s, const char delim);

public:
    explicit MarketDepthMessage(const std::string& message);

    void printMarketDepth();
};

static void printVec(std::vector<Order>& orders);