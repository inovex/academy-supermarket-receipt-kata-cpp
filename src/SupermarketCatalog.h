#pragma once

#include <memory>
#include <vector>

#include "Product.h"

class SupermarketCatalog
{
public:
  virtual void addProduct(std::shared_ptr<Product> product, double price) = 0;
  virtual double getUnitPrice(std::shared_ptr<Product> product) const = 0;
  virtual std::vector<Product> findProductsByPrice(double price) const = 0;
};
