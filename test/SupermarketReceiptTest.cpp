#include <memory>

#include "ProductUnit.h"
#include "ReceiptPrinter.h"
#include "ShoppingCart.h"
#include "Teller.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Eq;
using ::testing::Return;

class SupermarketReceiptTest : public ::testing::Test
{
protected:
  std::shared_ptr<Product> apples;
  std::shared_ptr<Product> toothbrush;
  double toothbrushPrice = 0.99;
  double applesPrice = 1.99;
  std::string expectedReceipt;

  void SetUp() override
  {
    apples = std::make_unique<Product>("apples", ProductUnit::Kilo);
    toothbrush = std::make_unique<Product>("toothbrush", ProductUnit::Each);
    expectedReceipt = "apples                              4.97\n"
                      "  1.99 * 2.500\n"
                      "toothbrush                          2.97\n"
                      "  0.99 * 3\n"
                      "10.0% off(toothbrush)              -0.30\n"
                      "\n"
                      "Total:                              7.65";
  }

  std::unique_ptr<ShoppingCart> createShoppingCart()
  {
    auto cart = std::make_unique<ShoppingCart>();

    cart->addItemQuantity(apples, 2.5);
    cart->addItemQuantity(toothbrush, 3);

    return cart;
  }

  std::unique_ptr<Teller> createTeller(const SupermarketCatalog &catalog)
  {
    auto teller = std::make_unique<Teller>(catalog);
    teller->addSpecialOffer(SpecialOfferType::TenPercentDiscount, toothbrush,
                            10.0);
    return teller;
  }
};

class SupermarketCatalogMock : public SupermarketCatalog
{
public:
  MOCK_METHOD(void, addProduct, (std::shared_ptr<Product> product, double),
              (override));
  MOCK_METHOD(double, getUnitPrice, (std::shared_ptr<Product> product),
              (const, override));
  MOCK_METHOD(std::vector<Product>, findProductsByPrice, (double),
              (const, override));
};

TEST_F(SupermarketReceiptTest, SystemTest)
{
  SupermarketCatalogMock catalog;
  EXPECT_CALL(catalog, getUnitPrice(Eq(apples)))
      .WillRepeatedly(Return(applesPrice));
  EXPECT_CALL(catalog, getUnitPrice(Eq(toothbrush)))
      .WillRepeatedly(Return(toothbrushPrice));

  auto cart = createShoppingCart();
  auto teller = createTeller(catalog);
  auto receipt = teller->checksOutArticlesFrom(*cart);

  ReceiptPrinter printer;
  auto printed = printer.printReceipt(*receipt);
  std::cout << printed << std::endl;

  ASSERT_EQ(expectedReceipt, printed);
}
