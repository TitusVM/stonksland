#pragma once

#include <QString>

class Currency
{
public:
  Currency(QString name, QString symbol, QString iso);

  QString getName() const;
  QString getSymbol() const;
  QString getISO() const;

  bool operator==(Currency const& rhs);

protected:
  QString name;
  QString symbol;
  QString iso;
};

