#pragma once
#include <memory>
#include <vector>

#include "DisC.h"
#include "ReceiptItem.h"

class Receipt
{
public:
  double getTotalPrice() const;

  void addProduct(std::shared_ptr<Product> p, double quantity, double price,
                  double totalPrice);

  const std::vector<std::unique_ptr<ReceiptItem>> &getItems() const;

  void addDiscount(std::unique_ptr<DisC> discount);

  const std::vector<std::unique_ptr<DisC>> &getDiscounts() const;

private:
  std::vector<std::unique_ptr<ReceiptItem>> items;
  std::vector<std::unique_ptr<DisC>> discounts;
};
