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

    friend std::ostream & operator<<(std::ostream &os, const TopOfBook &obj) {
        return os
               << "updateId: " << obj.updateId
               << " symbol: " << obj.symbol
               << " bestBid: " << obj.bestBid
               << " | "
               << " bestAsk: " << obj.bestAsk;
    }
};
