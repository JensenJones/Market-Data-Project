#include "Order.hpp"

Order::Order::Order(const std::string &symbol, const OrderSide side, const OrderType type, const OrderExpiry expiry,
    const long double quantity, const long double price, const long double timestamp): symbol(symbol),
                                                                                       side(side),
                                                                                       type(type),
                                                                                       expiry(expiry),
                                                                                       quantity(quantity),
                                                                                       price(price),
                                                                                       timestamp(timestamp) {


}
