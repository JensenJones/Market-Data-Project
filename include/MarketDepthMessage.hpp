#pragma once

#include <Order.hpp>
#include <vector>
#include <print>

class MarketDepthMessage {
private:
    std::vector<Order> bids;
    std::vector<Order> asks;

    static std::vector<std::string> splitStringOnQuotes(const std::string& s);

public:
    explicit MarketDepthMessage(const std::string& message);

    void printMarketDepth();
};

static void printVec(std::vector<Order>& orders);