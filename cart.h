#ifndef CART_H
#define CART_H

#include "product.h"
#include <vector>
#include <string>

class Cart {
private:
    vector<Product*> products;

public:
    ~Cart();

    void addProduct(const string& _name, int _quantity, vector<Product*>& availableProducts);
    void removeProduct(const string& _name, int _quantity, vector<Product*>& availableProducts);
    void printCart() const;
    float getTotalPrice() const;
    const vector<Product*>& getProducts() const;
    void clearCart();
};

#endif // CART_H