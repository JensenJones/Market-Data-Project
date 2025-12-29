#pragma once
#include <optional>

#include "Order.hpp"

class OrderFactory {
    bool hasPrice{};
    double price{};
    Order order;

public:
    std::optional<Order> newData(double newData);
};
