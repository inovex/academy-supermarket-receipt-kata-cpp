/****************************** File Header ******************************\
File Name:    Product.cpp
Project:      Super Market Receipt
Author:       cmenzel

Description:

Copyright (c) inovex GmbH
\***************************************************************************/
#include "Product.h"

/*
 * Der Konstruktor bekommt einen Namen und die ProductUnit.
 * */
Product::Product(std::string name, ProductUnit unit) : n(name), u(unit) {}

// Returns the Name of the product
std::string Product::ProductName() const { return n; }

// Returns the unit of the product
ProductUnit Product::provideUnit() const { return u; }