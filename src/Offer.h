#pragma once

#include <memory>

#include "Product.h"
#include "SpecialOfferType.h"

class Offer
{
public:
  Offer(SpecialOfferType offerType, std::shared_ptr<Product> product,
        double argument);

  std::shared_ptr<Product> getProduct();

  SpecialOfferType offerType;
  double argument;

private:
  std::shared_ptr<Product> product;
};
