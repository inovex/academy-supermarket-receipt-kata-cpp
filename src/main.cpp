#include <iostream>
#include <memory>

#include "ProductUnit.h"
#include "ReceiptPrinter.h"
#include "ShoppingCart.h"
#include "Teller.h"

int main(int argc, char **argv)
{
  std::shared_ptr<Product> apples =
      std::make_unique<Product>("apples", ProductUnit::Kilo);
  std::shared_ptr<Product> toothbrush =
      std::make_unique<Product>("toothbrush", ProductUnit::Each);

  std::shared_ptr<SupermarketCatalog> catalog;
  // TODO: catalog needs to be initialized

  auto teller = std::make_unique<Teller>(*catalog);
  teller->addSpecialOffer(SpecialOfferType::TenPercentDiscount, toothbrush,
                          10.0);

  auto cart = std::make_unique<ShoppingCart>();
  cart->addItemQuantity(apples, 2.5);
  cart->addItemQuantity(toothbrush, 3);

  auto receipt = teller->checksOutArticlesFrom(*cart);

  ReceiptPrinter printer;
  auto printed = printer.printReceipt(*receipt);
  std::cout << printed << std::endl;
}