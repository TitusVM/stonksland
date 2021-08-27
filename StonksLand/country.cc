#include "country.h"

Country::Country(QString name, Currency currency):
    name(name), currency(currency)
{
}

QString Country::getName() const {
  return name;
}

Currency Country::getCurrency() const {
  return currency;
}
