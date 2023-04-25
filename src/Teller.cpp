#include "Teller.h"

Teller::Teller(const SupermarketCatalog &catalog) : catalog(catalog) {}

void Teller::addSpecialOffer(SpecialOfferType offerType,
                             std::shared_ptr<Product> product,
                             double argument)
{
  offers[product] = std::make_shared<Offer>(offerType, product, argument);
}

std::unique_ptr<Receipt> Teller::checksOutArticlesFrom(ShoppingCart &theCart)
{
  auto receipt = std::make_unique<Receipt>();
  std::vector<PQ> productQuantities = theCart.getItems();

  for (int i = 0; i < productQuantities.size(); i++)
  {
    auto p = productQuantities[i].gebeProductZurueck();
    double quantity = productQuantities[i].getQuantity();
    double unitPrice = this->catalog.getUnitPrice(p);
    double price = quantity * unitPrice;
    receipt->addProduct(p, quantity, unitPrice, price);
  }
  theCart.handleOffers(*receipt, offers, this->catalog);

  return receipt;
}
