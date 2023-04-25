#pragma once

#include <memory>

#include "Product.h"

class ReceiptItem
{
public:
  ReceiptItem(std::shared_ptr<Product> p, double quantity, double price,
              double totalPrice);

  double getPrice();

  std::shared_ptr<Product> getProduct();

  double getQuantity();

  double getTotalPrice();

private:
  const std::shared_ptr<Product> product;
  const double price;
  double totalPrice;
  const double quantity;
};