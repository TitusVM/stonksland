#include "currency.h"

Currency::Currency(QString name, QString symbol, QString iso):
    name(name), symbol(symbol), iso(iso)
{
}

QString Currency::getName() const {
  return name;
}

QString Currency::getSymbol() const {
  return symbol;
}

QString Currency::getISO() const {
  return iso;
}

bool Currency::operator==(Currency const& rhs) const {
  return iso == rhs.iso;
}
