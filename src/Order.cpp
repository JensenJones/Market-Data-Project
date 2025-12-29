#include "../include/Order.hpp"

Order::Order() : price{ 0.0 }, quantity{ 0.0 } {}

Order::Order(const double price, const double quantity) : price{ price }, quantity{ quantity } {}

void Order::set_price(const double newPrice) {
    this->price = newPrice;
}


void Order::set_quantity(const double newQuantity) {
    this->quantity = newQuantity;
}

double Order::getPrice() const { return price; }

double Order::getQuantity() const { return quantity; }
