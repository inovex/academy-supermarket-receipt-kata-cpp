#pragma once
#include <memory>

#include "Product.h"

class PQ
{
public:
  PQ(std::shared_ptr<Product> p, double weight);

  std::shared_ptr<Product> gebeProductZurueck() const;

  double getQuantity() const;

private:
  const std::shared_ptr<Product> p;
  const double weight;
};
