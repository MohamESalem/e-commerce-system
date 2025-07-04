#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product {
protected:
    string name;
    float price;
    int quantity;

public:
    Product(const string& _name, float _price, int _quantity)
        : name(_name), price(_price), quantity(_quantity) {}

    virtual ~Product() = default;
    Product(const Product& other)
        : name(other.name), price(other.price), quantity(other.quantity) {}
    virtual bool isExpirable() const { return false; }
    virtual bool requiresShipping() const { return false; }

    // Clone function
    virtual Product* clone() const { return new Product(*this); }

    // Getters
    string getName() const { return name; }
    float getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    // Setters
    void setName(const string& _name) { name = _name; }
    void setPrice(float _price) { price = _price; }
    void setQuantity(int _quantity) { quantity = _quantity; }
};

class Expirable {
protected:
    string expiryDate;

public:
    Expirable(const string& _expiryDate) : expiryDate(_expiryDate) {}
    virtual ~Expirable() = default;

    // Getter
    string getExpiryDate() const { return expiryDate; }
    // Setter
    void setExpiryDate(const string& _expiryDate) { expiryDate = _expiryDate; }
};

class Shippable {
protected:
    float weight;

public:
    Shippable(float _weight) : weight(_weight) {}
    virtual ~Shippable() = default;

    // Getter
    float getWeight() const { return weight; }
    // Setter
    void setWeight(float _weight) { weight = _weight; }
};

class ExpirableProduct : public Product, public Expirable {
public:
    ExpirableProduct(const string& _name, float _price, int _quantity, const string& _expiryDate)
        : Product(_name, _price, _quantity), Expirable(_expiryDate) {}

    ExpirableProduct(const ExpirableProduct& other)
        : Product(other), Expirable(other) {}

    bool isExpirable() const override { return true; }

    Product* clone() const override { return new ExpirableProduct(*this); }
};

class ShippableProduct : public Product, public Shippable {
public:
    ShippableProduct(const string& _name, float _price, int _quantity, float _weight)
        : Product(_name, _price, _quantity), Shippable(_weight) {}

    ShippableProduct(const ShippableProduct& other)
        : Product(other), Shippable(other) {}

    bool requiresShipping() const override { return true; }

    Product* clone() const override { return new ShippableProduct(*this); }
};

class ExpirableShippableProduct : public Product, public Expirable, public Shippable {
public:
    ExpirableShippableProduct(const string& _name, float _price, int _quantity, const string& _expiryDate, float _weight)
        : Product(_name, _price, _quantity), Expirable(_expiryDate), Shippable(_weight) {}

    ExpirableShippableProduct(const ExpirableShippableProduct& other)
        : Product(other), Expirable(other), Shippable(other) {}

    bool isExpirable() const override { return true; }
    bool requiresShipping() const override { return true; }

    Product* clone() const override { return new ExpirableShippableProduct(*this); }
};

#endif // PRODUCT_H
