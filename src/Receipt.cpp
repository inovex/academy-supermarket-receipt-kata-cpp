#include "Receipt.h"

double Receipt::getTotalPrice() const
{
  double total = 0.0;
  for (auto &item : items)
  {
    total += item->getTotalPrice();
  }
  for (auto &discount : discounts)
  {
    total -= discount->getAmount();
  }
  return total;
}

void Receipt::addProduct(std::shared_ptr<Product> p, double quantity,
                         double price, double totalPrice)
{
  items.push_back(
      std::make_unique<ReceiptItem>(p, quantity, price, totalPrice));
}

const std::vector<std::unique_ptr<ReceiptItem>> &Receipt::getItems() const
{
  return items;
}

void Receipt::addDiscount(std::unique_ptr<DisC> discount)
{
  discounts.push_back(std::move(discount));
}

const std::vector<std::unique_ptr<DisC>> &Receipt::getDiscounts() const
{
  return discounts;
}
