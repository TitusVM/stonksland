#pragma once

#include <vector>

#include "country.h"
#include "currency.h"

class GetInfo
{
public:
  GetInfo(std::vector<Country> countries, std::vector<Currency> currencies);
  GetInfo(QString filename);

  std::vector<Country> findCountries(Currency currency);
  Country findCountry(QString name);
  Currency findCurrency(Country country);

protected:
  std::vector<Country> countries;
  std::vector<Currency> currencies;
};

