#include "cart.h"
#include <iostream>
#include <iomanip>

using namespace std;

Cart::~Cart() {
    clearCart();
}

void Cart::clearCart() {
    for (Product* p : products) {
        delete p;
    }
    products.clear();
}

void Cart::addProduct(const string& _name, int _quantity, vector<Product*>& availableProducts) {
    Product* marketProd = nullptr;
    for (auto& p : availableProducts) {
        if (p->getName() == _name) {
            marketProd = p;
            break;
        }
    }

    if (marketProd == nullptr) {
        cout << "Error: Product '" << _name << "' not found in the market." << endl;
        return;
    }
    if (marketProd->getQuantity() < _quantity) {
        cout << "Error: Not enough stock for '" << _name << "'. Available: " << marketProd->getQuantity() << ", Requested: " << _quantity << "." << endl;
        return;
    }

    for (auto& cartProd : products) {
        if (cartProd->getName() == _name) {
            cartProd->setQuantity(cartProd->getQuantity() + _quantity);
            marketProd->setQuantity(marketProd->getQuantity() - _quantity);
            cout << "Updated cart: '" << _name << "' quantity is now " << cartProd->getQuantity() << "." << endl;
            return;
        }
    }

    Product* newCartProd = marketProd->clone();
    newCartProd->setQuantity(_quantity);
    products.push_back(newCartProd);

    marketProd->setQuantity(marketProd->getQuantity() - _quantity);
    cout << "Added " << _quantity << " of '" << _name << "' to the cart." << endl;
}

void Cart::removeProduct(const string& _name, int _quantity, vector<Product*>& availableProducts) {
    auto it = products.begin();
    while (it != products.end()) {
        if ((*it)->getName() == _name) {
            if ((*it)->getQuantity() < _quantity) {
                cout << "Error: Cannot remove " << _quantity << " of '" << _name << "'. You only have " << (*it)->getQuantity() << " in your cart." << endl;
                return;
            }

            (*it)->setQuantity((*it)->getQuantity() - _quantity);

            for (auto& marketProd : availableProducts) {
                if (marketProd->getName() == _name) {
                    marketProd->setQuantity(marketProd->getQuantity() + _quantity);
                    break;
                }
            }
            
            cout << "Removed " << _quantity << " of '" << _name << "' from the cart." << endl;

            if ((*it)->getQuantity() == 0) {
                cout << "'" << _name << "' has been completely removed from the cart." << endl;
                delete *it; 
                products.erase(it);
            }
            return;
        }
        ++it;
    }
    cout << "Error: Product '" << _name << "' not found in your cart." << endl;
}

void Cart::printCart() const {
    cout << "\n--- Your Shopping Cart ---" << endl;
    if (products.empty()) {
        cout << "Cart is empty." << endl;
        return;
    }
    cout << left << setw(20) << "Product"
         << setw(10) << "Price"
         << setw(10) << "Quantity"
         << setw(10) << "Subtotal" << endl;
    cout << string(50, '-') << endl;
    float total = 0;
    for (const auto& prod : products) {
        float subtotal = prod->getPrice() * prod->getQuantity();
        cout << left << setw(20) << prod->getName()
             << setw(10) << fixed << setprecision(2) << prod->getPrice()
             << setw(10) << prod->getQuantity()
             << setw(10) << fixed << setprecision(2) << subtotal << endl;
        total += subtotal;
    }
    cout << string(50, '-') << endl;
    cout << left << setw(40) << "Total:" << fixed << setprecision(2) << total << endl;
    cout << "--------------------------\n" << endl;
}

float Cart::getTotalPrice() const {
    float total = 0;
    for (const auto& prod : products) {
        total += prod->getPrice() * prod->getQuantity();
    }
    return total;
}

const vector<Product*>& Cart::getProducts() const {
    return products;
}