#include "shippingservice.h"

const float SHIPPING_RATE_PER_KG= 1.5f;

float ShippingService::calculateShippingFee(const vector<Product*>& items) const {
    float totalWeight = 0;
    for (const auto& item : items) {
        if(item->requiresShipping()) {
            const Shippable* shippableItem = dynamic_cast<const Shippable*>(item);
            if (shippableItem) {
                totalWeight += shippableItem->getWeight() * item->getQuantity();
            }
        } 
    }

    return totalWeight * SHIPPING_RATE_PER_KG;
}