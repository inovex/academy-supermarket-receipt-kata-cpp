#include "Offer.h"

Offer::Offer(SpecialOfferType offerType, std::shared_ptr<Product> product,
             double argument)
    : offerType(offerType), product(product), argument(argument) {}

std::shared_ptr<Product> Offer::getProduct() { return product; }
