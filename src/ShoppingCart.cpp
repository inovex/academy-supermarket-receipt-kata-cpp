#include "ShoppingCart.h"

#include <iomanip>
#include <sstream>

const std::vector<PQ> &ShoppingCart::getItems() { return items; }

void ShoppingCart::addItem(std::shared_ptr<Product> product)
{
  addItemQuantity(product, 1.0);
}

const std::map<std::shared_ptr<Product>, double> &
ShoppingCart::productQuantitiesMap()
{
  return productQuantities;
}

void ShoppingCart::addItemQuantity(std::shared_ptr<Product> product,
                                   double quantity)
{
  items.push_back(PQ(product, quantity));
  if (productQuantities.count(product) != 0)
  {
    productQuantities[product] += quantity;
  }
  else
  {
    productQuantities[product] = quantity;
  }
}

void ShoppingCart::handleOffers(
    Receipt &receipt,
    std::map<std::shared_ptr<Product>, std::shared_ptr<Offer>> offers,
    const SupermarketCatalog &catalog)
{
  for (const auto &[p, qu] : productQuantitiesMap())
  {
    if (offers.count(p) != 0)
    {
      auto &of = offers[p];
      double uP = catalog.getUnitPrice(p);
      int iQuantity = (int)qu;
      std::unique_ptr<DisC> discount;
      int x = 1;
      if (of->offerType == SpecialOfferType::ThreeForTwo)
      {
        x = 3;
      }
      else if (of->offerType == SpecialOfferType::TwoForAmount)
      {
        x = 2;
        if (iQuantity >= 2)
        {
          double dTotal = of->argument * iQuantity / x + iQuantity % 2 * uP;
          double dDiscountN = uP * qu - dTotal;
          discount = std::make_unique<DisC>(
              p, "2 for " + std::to_string(of->argument), dDiscountN);
        }
      }
      if (of->offerType == SpecialOfferType::FiveForAmount)
      {
        x = 5;
      }
      int numberOfXs = iQuantity / x;
      if (of->offerType == SpecialOfferType::ThreeForTwo && iQuantity > 2)
      {
        double dDiscountAmount =
            qu * uP - ((numberOfXs * 2 * uP) + iQuantity % 3 * uP);
        discount = std::make_unique<DisC>(p, "3 for 2", dDiscountAmount);
      }
      if (of->offerType == SpecialOfferType::TenPercentDiscount)
      {
        discount = std::make_unique<DisC>(
            p, getFormattedNumberAsString(of->argument, 1) + "% off",
            qu * uP * of->argument / 100.0);
      }
      if (of->offerType == SpecialOfferType::FiveForAmount && iQuantity >= 5)
      {
        double dDiscountTotal =
            uP * qu - (of->argument * numberOfXs + iQuantity % 5 * uP);
        discount = std::make_unique<DisC>(
            p, x + " for " + std::to_string(of->argument), dDiscountTotal);
      }
      if (discount)
        receipt.addDiscount(std::move(discount));
    }
  }
}

std::string ShoppingCart::getFormattedNumberAsString(double number,
                                                     int precision)
{
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << number;
  return stream.str();
}
