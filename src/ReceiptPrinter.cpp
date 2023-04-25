#include "ReceiptPrinter.h"

#include <iomanip>
#include <sstream>

ReceiptPrinter::ReceiptPrinter() : ReceiptPrinter(40) {}

ReceiptPrinter::ReceiptPrinter(int columns) : columns(columns) {}

std::string ReceiptPrinter::printReceipt(const Receipt &receipt)
{
  std::string result;
  for (auto &item : receipt.getItems())
  {
    std::string price = getFormattedNumberAsString(item->getTotalPrice(), 2);
    std::string name = item->getProduct()->ProductName();
    std::string quantity = presentQuantity(*item);
    std::string unitPrice = getFormattedNumberAsString(item->getPrice(), 2);

    int whitespaceSize = columns - name.length() - price.length();
    std::string line = name + getWhitespace(whitespaceSize) + price + "\n";

    if (item->getQuantity() != 1)
    {
      line += "  " + unitPrice + " * " + quantity + "\n";
    }
    result.append(line);
  }
  for (auto &discount : receipt.getDiscounts())
  {
    std::string productPresentation = discount->returnProduct()->ProductName();
    std::string pricePresentation =
        getFormattedNumberAsString(discount->getAmount(), 2);
    std::string description = discount->gebeBeschreibung();
    result.append(description);
    result.append("(");
    result.append(productPresentation);
    result.append(")");
    result.append(getWhitespace(columns - 3 - productPresentation.length() -
                                description.length() -
                                pricePresentation.length()));
    result.append("-");
    result.append(pricePresentation);
    result.append("\n");
  }
  result.append("\n");
  std::string pricePresentation =
      getFormattedNumberAsString(receipt.getTotalPrice(), 2);
  std::string total = "Total: ";
  std::string whitespace =
      getWhitespace(columns - total.length() - pricePresentation.length());
  result.append(total).append(whitespace).append(pricePresentation);
  return result;
}

std::string ReceiptPrinter::presentQuantity(ReceiptItem &item)
{
  return ProductUnit::Each == item.getProduct()->provideUnit()
             ? getFormattedNumberAsString(item.getQuantity(), 0)
             : getFormattedNumberAsString(item.getQuantity(), 3);
}

std::string ReceiptPrinter::getWhitespace(int whitespaceSize)
{
  return std::string(whitespaceSize, ' ');
}

std::string ReceiptPrinter::getFormattedNumberAsString(double number,
                                                       int precision)
{
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << number;
  return stream.str();
}
