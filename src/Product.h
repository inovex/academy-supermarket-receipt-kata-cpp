/****************************** File Header ******************************\
File Name:    Product.h
Project:      Super Market Receipt
Author:       cmenzel

Description:

Copyright (c) inovex GmbH
\***************************************************************************/
#pragma once

#include <string>

#include "ProductUnit.h"
/*
 * The class product contains a name and the produc unit.
 */
class Product
{
private:
  const std::string n;
  const ProductUnit u;

public:
  Product(std::string name, ProductUnit unit);

  std::string ProductName() const;

  ProductUnit provideUnit() const;
};
