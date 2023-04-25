#pragma once

#include <memory>
#include <string>

#include "Product.h"

class DisC
{
private:
  const std::string d; // Description
  const double hoeheDesNachlasses;
  std::shared_ptr<Product> p;

public:
  DisC(std::shared_ptr<Product> p, std::string desc, double amount);

  std::string gebeBeschreibung();

  double getAmount();

  std::shared_ptr<Product> returnProduct();
};
