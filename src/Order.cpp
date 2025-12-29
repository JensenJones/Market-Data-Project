#include "../include/Order.hpp"

Order::Order() : price{ 0.0 }, quantity{ 0.0 } {}

Order::Order(const double price, const double quantity) : price{ price }, quantity{ quantity } {}

double Order::getPrice() const { return price; }

double Order::getQuantity() const { return quantity; }
