#include "DisC.h"

DisC::DisC(std::shared_ptr<Product> p, std::string desc, double amount)
    : d(desc), hoeheDesNachlasses(amount), p(p) {}

std::string DisC::gebeBeschreibung() { return d; }

double DisC::getAmount() { return hoeheDesNachlasses; }

std::shared_ptr<Product> DisC::returnProduct() { return p; }
