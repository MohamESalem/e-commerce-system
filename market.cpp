#include "market.h"
#include <iostream>
#include <iomanip>

#include <string>
#include <ctime>

using namespace std;

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm =localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
    return string(buffer);
}


Market::Market() {
    cout << "Welcome to the Market!" << endl;
    availableProducts.push_back(new ExpirableProduct("Milk", 2.50, 20, "2025-07-20"));
    availableProducts.push_back(new ExpirableProduct("Cheese", 5.00, 15, "2025-08-15"));
    availableProducts.push_back(new ExpirableProduct("Expired Yoghurt", 3.00, 10, "2024-01-01")); //this item is expired
    availableProducts.push_back(new ShippableProduct("Laptop", 1200.00, 5, 2.2f));
    availableProducts.push_back(new ShippableProduct("Book", 15.99, 30, 0.5f));
    availableProducts.push_back(new ExpirableShippableProduct("Sausages", 8.50, 10, "2025-07-12", 1.0f));
    availableProducts.push_back(new Product("Water Bottle", 1.00, 50));
}

Market::~Market() {
    cout << "\nClosing the Market. Cleaning up..." << endl;
    for (Product* p : availableProducts) {
        delete p;
    }
    availableProducts.clear();
}

void Market::setUserBudget(float budget) {
    currentUser.setBudget(budget);
    cout << "User budget has been set to $" << fixed << setprecision(2) << budget << "." << endl;
}

void Market::printAvailableProducts() const {
    cout << "\n Available Products in the Market " << endl;
    cout << left << setw(20) << "Product"
         << setw(10) << "Price"
         << setw(10) << "Stock" << endl;
    cout << string(40, '-') << endl;
    for (const auto& prod : availableProducts) {
        cout << left << setw(20) << prod->getName()
             << setw(10) << fixed << setprecision(2) << prod->getPrice()
             << setw(10) << prod->getQuantity() << endl;
    }
    cout << "----------------------------------------\n" << endl;
}

void Market::addToCart(const string& name, int quantity) {
    userCart.addProduct(name, quantity, availableProducts);
}

void Market::removeFromCart(const string& name, int quantity) {
    userCart.removeProduct(name, quantity, availableProducts);
}

void Market::printCart() const {
    userCart.printCart();
}

void Market::checkOut() {
    cout << "\n--- Checking Out ---" << endl;
    const auto& cartProducts = userCart.getProducts();

    if (cartProducts.empty()) {
        cout << "Checkout failed: Your cart is empty." << endl;
        cout << "--------------------" << endl;
        return;
    }



    //Check for expired products
    string today = getCurrentDate();
    for (const auto& product : cartProducts) {
        if (product->isExpirable()) {
            const ExpirableProduct* expirable = dynamic_cast<const ExpirableProduct*>(product);
            if (expirable && expirable->getExpiryDate() < today) {
                cout << "Checkout failed: Product '" << product->getName() 
                     << "' is expired (Expiry Date: " << expirable->getExpiryDate() << ")." << endl;
                cout << "--------------------" << endl;
                return;
            }
        }
    }

    //Calculate subtotal and collect shippable items
    float subtotal = userCart.getTotalPrice();
    vector<Product*> shippableItems;
    for (auto& product : cartProducts) {
        if (product->requiresShipping()) {
            shippableItems.push_back(product);
        }
    }

    //Calculate shipping fees
    float shippingFee = shippingService.calculateShippingFee(shippableItems);
    float totalAmount = subtotal + shippingFee;
    float budget = currentUser.getBudget();

    // Check budget
    if (totalAmount > budget) {
        cout << "Checkout failed: Insufficient funds." << endl;
        cout << "Required: $" << fixed << setprecision(2) << totalAmount
             << " | Your Budget: $" << budget << endl;
        cout << "You are short by $" << fixed << setprecision(2) << (totalAmount - budget) << "." << endl;
        cout << "--------------------" << endl;
        return;
    }

    //Process payment and print details
    cout << "-----------------------------------" << endl;
    float newBudget = budget - totalAmount;
    currentUser.setBudget(newBudget);
    cout << left << setw(15) << "Product"
         << setw(10) << "Amount"
         << setw(10) << "Weight"
         << setw(10) << "Price" << endl;
    cout << string(45, '-') << endl;
    for (const auto& product : cartProducts) {
        int amount = product->getQuantity();
        float weight = 0.0f;
        if (product->requiresShipping()) {
            const ShippableProduct* ship = dynamic_cast<const ShippableProduct*>(product);
            if (ship) weight = ship->getWeight() * amount;
        }
        float price = product->getPrice() * amount;
        cout << left << setw(15) << product->getName()
             << setw(10) << amount
             << setw(10) << fixed << setprecision(2) << weight
             << setw(10) << fixed << setprecision(2) << price << endl;
    }
    cout << "-----------------------------------" << endl;
    cout << "Checkout successful! Thank you for your purchase." << endl;
    cout << "--- Order Summary ---" << endl;
    cout << left << setw(25) << "Order Subtotal:" << "$" << fixed << setprecision(2) << subtotal << endl;
    cout << left << setw(25) << "Shipping Fees:" << "$" << fixed << setprecision(2) << shippingFee << endl;
    cout << left << setw(25) << "Total Paid Amount:" << "$" << fixed << setprecision(2) << totalAmount << endl;
    cout << "---------------------" << endl;
    cout << left << setw(25) << "Your New Budget:" << "$" << fixed << setprecision(2) << newBudget << endl;
    
    userCart.clearCart();
    cout << "--------------------" << endl;
}