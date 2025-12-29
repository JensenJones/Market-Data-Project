#pragma once

class Order {
    double price;
    double quantity;

public:
    Order();
    Order(double price, double quantity);

    double getPrice() const;

    double getQuantity() const;
};
