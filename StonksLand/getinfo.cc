#include "getinfo.h"

#include <algorithm>
#include <stdexcept>

#include "csv.h"

GetInfo::GetInfo(QString filename): countries(), currencies() {
  QFile file(filename);
  file.open(QFile::OpenModeFlag::ReadOnly);
  std::vector<std::vector<std::string>> table = readCSV(file);

  bool firstLine = true;
  for (std::vector<std::string> line : table) {
    /* skip headers */
    if (firstLine) {
      firstLine = false;
      continue;
    }

    QString countryName = QString::fromStdString(line[0]);
    QString currencyName = QString::fromStdString(line[1]);
    QString currencySymbol = QString::fromStdString(line[2]);
    QString currencyISO = QString::fromStdString(line[3]);

    Currency currency(currencyName, currencySymbol, currencyISO);
    auto it = std::find_if(currencies.begin(), currencies.end(),
    [&currency](auto& curr) { return curr == currency; } );

    if (it == currencies.end()) {
      currencies.push_back(currency);
    } else {
      currency = *it;
    }

    countries.push_back(Country(countryName, currency));
  }
}

std::vector<Country> GetInfo::findCountries(Currency currency) {
  std::vector<Country> found;
  std::vector<Country>::iterator it = countries.begin();
  do {
    it = std::find_if(it, countries.end(),
    [&currency](auto& country) { return country.getCurrency() == currency; });

    if (it != countries.end()) {
      found.push_back(*it);
      ++it;
    }

  } while (it != countries.end());

  return found;
}

Country GetInfo::findCountry(QString name) {
  auto it = std::find_if(countries.begin(), countries.end(),
  [&name](auto& country) { return country.getName() == name; });
  if (it == countries.end()) {
    throw std::runtime_error(std::string("Country with name \"") + name.toStdString() + "\" could not be found.");
  }

  return *it;
}

Currency GetInfo::findCurrency(Country country) {
  auto it = std::find_if(currencies.begin(), currencies.end(),
  [country](auto& currency) { return currency == country.getCurrency(); });
  if (it == currencies.end()) {
    throw std::runtime_error(std::string("Country \"") + country.getName().toStdString() + "\" has no currency.");
  }

  return *it;
}

Currency GetInfo::findCurrency(QString name) {
  auto it = std::find_if(currencies.begin(), currencies.end(),
  [&name](auto& currency) { return currency.getName() == name; });
  if (it == currencies.end()) {
    throw std::runtime_error(std::string("Currency \"") + name.toStdString() + "\" could not be found.");
  }

  return *it;
}

std::vector<Currency> GetInfo::getCurrencyList() const {
  return currencies;
}

