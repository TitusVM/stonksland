#pragma once

#include <vector>

#include "country.h"
#include "currency.h"

class GetInfo
{
public:
  GetInfo(QString filename, QString keys);

  std::vector<Country> findCountries(Currency currency);
  Country findCountry(QString name);
  Currency findCurrency(QString name);
  std::vector<Currency> getCurrencyList() const;
  QString getExchangeratesapiApiKey() const;
  QString getMarketstackApiKey() const;

protected:
  std::vector<Country> countries;
  std::vector<Currency> currencies;
  QString exchangeratesapiApiKey;
  QString marketstackApiKey;
};

