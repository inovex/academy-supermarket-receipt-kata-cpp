#pragma once
#include <map>
#include <memory>
#include <optional>
#include <vector>

#include "Offer.h"
#include "PQ.h"
#include "Product.h"
#include "Receipt.h"
#include "SpecialOfferType.h"
#include "SupermarketCatalog.h"

class ShoppingCart
{
public:
  const std::vector<PQ> &getItems();

  void addItem(std::shared_ptr<Product> product);

  const std::map<std::shared_ptr<Product>, double> &productQuantitiesMap();

  void addItemQuantity(std::shared_ptr<Product> product, double quantity);

  void handleOffers(
      Receipt &receipt,
      std::map<std::shared_ptr<Product>, std::shared_ptr<Offer>> offers,
      const SupermarketCatalog &catalog);

private:
  std::vector<PQ> items;
  std::map<std::shared_ptr<Product>, double> productQuantities;

  static std::string getFormattedNumberAsString(double number, int precision);
};
