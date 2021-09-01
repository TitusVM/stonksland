#pragma once

#include <vector>

#include "country.h"
#include "currency.h"

class GetInfo
{
public:
  GetInfo(QString filename);

  std::vector<Country> findCountries(Currency currency);
  Country findCountry(QString name);
  Currency findCurrency(QString name);

  std::vector<Currency> getCurrencyList() const;

protected:
  std::vector<Country> countries;
  std::vector<Currency> currencies;
};

