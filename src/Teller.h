#pragma once
#include <map>
#include <memory>

#include "Offer.h"
#include "ShoppingCart.h"
#include "SpecialOfferType.h"
#include "SupermarketCatalog.h"

class Teller
{
public:
  Teller(const SupermarketCatalog &catalog);

  void addSpecialOffer(SpecialOfferType offerType,
                       std::shared_ptr<Product> product, double argument);

  std::unique_ptr<Receipt> checksOutArticlesFrom(ShoppingCart &theCart);

private:
  const SupermarketCatalog &catalog;
  std::map<std::shared_ptr<Product>, std::shared_ptr<Offer>> offers;
};
