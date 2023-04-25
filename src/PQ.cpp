#include "PQ.h"

PQ::PQ(std::shared_ptr<Product> p, double weight) : p(p), weight(weight) {}

std::shared_ptr<Product> PQ::gebeProductZurueck() const { return p; }

double PQ::getQuantity() const { return weight; }
