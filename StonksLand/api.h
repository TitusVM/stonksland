#pragma once

#include <QDate>
#include <QMap>

class Api
{
public:
  Api(QString key);

  QString dl();
  QString dl(QDate date);

  static QMap<QString, double> extractRates(QString json);

protected:
  QString key;
};

