#ifndef MARKET_H
#define MARKET_H

#include "cart.h"
#include "user.h"
#include "shippingservice.h"
#include <vector>
#include <string>

class Market {
private:
    vector<Product*> availableProducts;
    Cart userCart;
    User currentUser;
    ShippingService shippingService;

public:
    Market();
    ~Market();

    void printAvailableProducts() const;
    void addToCart(const string& name, int quantity);
    void removeFromCart(const string& name, int quantity);
    void printCart() const;
    void checkOut();
    void setUserBudget(float budget);
};

#endif // MARKET_H