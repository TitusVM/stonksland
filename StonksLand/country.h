#pragma once

#include <QString>

#include "currency.h"

class Country
{
public:
  Country(QString name, Currency currency);

public:
  QString getName() const;
  Currency getCurrency() const;

protected:
  QString name;
  Currency currency;
};

