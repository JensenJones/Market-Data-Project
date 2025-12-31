#pragma once
#include <ostream>
#include <string>
#include <nlohmann/json_fwd.hpp>

#include "Order.hpp"

class TopOfBook {
    const uint64_t updateId;
    const std::string symbol;
    Order bestBid;
    Order bestAsk;

public:
    explicit TopOfBook(const nlohmann::json& marketMessage);

    TopOfBook(const TopOfBook &other) = default;

    TopOfBook(TopOfBook &&other) noexcept = default;

    TopOfBook(uint64_t updateId, std::string symbol, const Order &bestBid, const Order &bestAsk);

    friend std::ostream & operator<<(std::ostream &os, const TopOfBook &obj);
};
