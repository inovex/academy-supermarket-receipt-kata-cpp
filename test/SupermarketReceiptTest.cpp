#include <memory>

#include "ProductUnit.h"
#include "ReceiptPrinter.h"
#include "ShoppingCart.h"
#include "Teller.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Eq;
using ::testing::Return;

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

class SupermarketReceiptTest : public ::testing::Test
{
protected:
  std::shared_ptr<Product> apples;
  std::shared_ptr<Product> toothbrush;
  std::shared_ptr<Product> banana;
  std::shared_ptr<Product> orange;
  std::shared_ptr<Product> kiwi;
  double toothbrushPrice = 0.99;
  double applesPrice = 1.99;
  double bananaPrice = 1.99;
  double orangePrice = 1.99;
  double kiwiPrice = 1.99;

  void SetUp() override
  {
    apples = std::make_unique<Product>("apples", ProductUnit::Kilo);
    toothbrush = std::make_unique<Product>("toothbrush", ProductUnit::Each);
    banana = std::make_unique<Product>("banana", ProductUnit::Kilo);
    orange = std::make_unique<Product>("orange", ProductUnit::Kilo);
    kiwi = std::make_unique<Product>("kiwi", ProductUnit::Kilo);
  }

  std::unique_ptr<ShoppingCart> createShoppingCart()
  {
    auto cart = std::make_unique<ShoppingCart>();

    cart->addItemQuantity(apples, 2.5);
    cart->addItemQuantity(toothbrush, 3);
    cart->addItemQuantity(orange, 2);
    cart->addItemQuantity(kiwi, 5);
    cart->addItemQuantity(banana, 3);

    return cart;
  }

  std::shared_ptr<SupermarketCatalogMock> createCatalogMock()
  {
    auto catalog = std::make_shared<SupermarketCatalogMock>();
    EXPECT_CALL(*catalog, getUnitPrice(Eq(apples)))
        .WillRepeatedly(Return(applesPrice));
    EXPECT_CALL(*catalog, getUnitPrice(Eq(toothbrush)))
        .WillRepeatedly(Return(toothbrushPrice));
    EXPECT_CALL(*catalog, getUnitPrice(Eq(banana)))
        .WillRepeatedly(Return(bananaPrice));
    EXPECT_CALL(*catalog, getUnitPrice(Eq(orange)))
        .WillRepeatedly(Return(orangePrice));
    EXPECT_CALL(*catalog, getUnitPrice(Eq(kiwi)))
        .WillRepeatedly(Return(kiwiPrice));

    return catalog;
  }
};

TEST_F(SupermarketReceiptTest, printReceipt_noDiscoutnts_printsExpectedReceipt)
{
  auto catalog = createCatalogMock();
  auto cart = createShoppingCart();
  auto teller = std::make_unique<Teller>(*catalog);
  auto receipt = teller->checksOutArticlesFrom(*cart);

  ReceiptPrinter printer;
  auto printed = printer.printReceipt(*receipt);
  std::cout << printed << std::endl;

  auto expectedReceipt = "apples                              4.97\n"
                         "  1.99 * 2.500\n"
                         "toothbrush                          2.97\n"
                         "  0.99 * 3\n"
                         "orange                              3.98\n"
                         "  1.99 * 2.000\n"
                         "kiwi                                9.95\n"
                         "  1.99 * 5.000\n"
                         "banana                              5.97\n"
                         "  1.99 * 3.000\n"
                         "\n"
                         "Total:                             27.84";
  ASSERT_EQ(expectedReceipt, printed);
}

TEST_F(SupermarketReceiptTest, printReceipt_tenPercentDiscount_printsExpectedReceipt)
{
  auto catalog = createCatalogMock();
  auto cart = createShoppingCart();
  auto teller = std::make_unique<Teller>(*catalog);
  teller->addSpecialOffer(SpecialOfferType::TenPercentDiscount, toothbrush, 10.0);
  auto receipt = teller->checksOutArticlesFrom(*cart);

  ReceiptPrinter printer;
  auto printed = printer.printReceipt(*receipt);
  std::cout << printed << std::endl;

  auto expectedReceipt = "apples                              4.97\n"
                         "  1.99 * 2.500\n"
                         "toothbrush                          2.97\n"
                         "  0.99 * 3\n"
                         "orange                              3.98\n"
                         "  1.99 * 2.000\n"
                         "kiwi                                9.95\n"
                         "  1.99 * 5.000\n"
                         "banana                              5.97\n"
                         "  1.99 * 3.000\n"
                         "10.0% off(toothbrush)              -0.30\n"
                         "\n"
                         "Total:                             27.55";
  ASSERT_EQ(expectedReceipt, printed);
}

TEST_F(SupermarketReceiptTest, printReceipt_threeForTwo_printsExpectedReceipt)
{
  auto catalog = createCatalogMock();
  auto cart = createShoppingCart();
  auto teller = std::make_unique<Teller>(*catalog);
  teller->addSpecialOffer(SpecialOfferType::ThreeForTwo, banana, 2.0);
  auto receipt = teller->checksOutArticlesFrom(*cart);

  ReceiptPrinter printer;
  auto printed = printer.printReceipt(*receipt);
  std::cout << printed << std::endl;

  auto expectedReceipt = "apples                              4.97\n"
                         "  1.99 * 2.500\n"
                         "toothbrush                          2.97\n"
                         "  0.99 * 3\n"
                         "orange                              3.98\n"
                         "  1.99 * 2.000\n"
                         "kiwi                                9.95\n"
                         "  1.99 * 5.000\n"
                         "banana                              5.97\n"
                         "  1.99 * 3.000\n"
                         "3 for 2(banana)                    -1.99\n"
                         "\n"
                         "Total:                             25.86";
  ASSERT_EQ(expectedReceipt, printed);
}

TEST_F(SupermarketReceiptTest, printReceipt_twoForAmount_printsExpectedReceipt)
{
  auto catalog = createCatalogMock();
  auto cart = createShoppingCart();
  auto teller = std::make_unique<Teller>(*catalog);
  teller->addSpecialOffer(SpecialOfferType::TwoForAmount, orange, 2.5);
  auto receipt = teller->checksOutArticlesFrom(*cart);

  ReceiptPrinter printer;
  auto printed = printer.printReceipt(*receipt);
  std::cout << printed << std::endl;

  auto expectedReceipt = "apples                              4.97\n"
                         "  1.99 * 2.500\n"
                         "toothbrush                          2.97\n"
                         "  0.99 * 3\n"
                         "orange                              3.98\n"
                         "  1.99 * 2.000\n"
                         "kiwi                                9.95\n"
                         "  1.99 * 5.000\n"
                         "banana                              5.97\n"
                         "  1.99 * 3.000\n"
                         "2 for 2.500000(orange)             -1.48\n"
                         "\n"
                         "Total:                             26.36";
  ASSERT_EQ(expectedReceipt, printed);
}

TEST_F(SupermarketReceiptTest, printReceipt_fiveForAmount_printsExpectedReceipt)
{
  auto catalog = createCatalogMock();
  auto cart = createShoppingCart();
  auto teller = std::make_unique<Teller>(*catalog);
  teller->addSpecialOffer(SpecialOfferType::FiveForAmount, kiwi, 5.5);
  auto receipt = teller->checksOutArticlesFrom(*cart);

  ReceiptPrinter printer;
  auto printed = printer.printReceipt(*receipt);
  std::cout << printed << std::endl;

  auto expectedReceipt = "apples                              4.97\n"
                         "  1.99 * 2.500\n"
                         "toothbrush                          2.97\n"
                         "  0.99 * 3\n"
                         "orange                              3.98\n"
                         "  1.99 * 2.000\n"
                         "kiwi                                9.95\n"
                         "  1.99 * 5.000\n"
                         "banana                              5.97\n"
                         "  1.99 * 3.000\n"
                         "5.500000(kiwi)                     -4.45\n"
                         "\n"
                         "Total:                             23.39";
  ASSERT_EQ(expectedReceipt, printed);
}