#ifndef SHIPPING_SERVICE_H
#define SHIPPING_SERVICE_H

#include "product.h"
#include <vector>

class ShippingService {
public:
    float calculateShippingFee(const vector<Product*>& items) const;
};

#endif 