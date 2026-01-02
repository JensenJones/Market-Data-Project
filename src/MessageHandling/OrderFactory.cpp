#include "../../include/MessageHandling/OrderFactory.hpp"

std::optional<Order> OrderFactory::newData(double newData) {
    if (!hasPrice) {
        price = newData;
        hasPrice = true;
        return std::nullopt;
    }
    hasPrice = false;
    return std::make_optional<Order>(Order(price, newData));
}
