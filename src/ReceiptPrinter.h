#pragma once

#include "Receipt.h"

class ReceiptPrinter
{
public:
  ReceiptPrinter();
  ReceiptPrinter(int columns);

  std::string printReceipt(const Receipt &receipt);

  static std::string presentQuantity(ReceiptItem &item);

  static std::string getWhitespace(int whitespaceSize);

private:
  static std::string getFormattedNumberAsString(double number, int precision);

  const int columns;
};
