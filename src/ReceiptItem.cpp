#include "ReceiptItem.h"

ReceiptItem::ReceiptItem(std::shared_ptr<Product> p, double quantity,
                         double price, double totalPrice)
    : product(p), quantity(quantity), price(price), totalPrice(totalPrice) {}

double ReceiptItem::getPrice() { return price; }

std::shared_ptr<Product> ReceiptItem::getProduct() { return product; }

double ReceiptItem::getQuantity() { return quantity; }

double ReceiptItem::getTotalPrice() { return totalPrice; }
