#pragma once

#include <QMap>

class Cache
{
public:
  Cache(QString directory, int validity = 24 * 60 * 60);

  bool contains(QString name);
  QString get(QString name);
  void add(QString name, QString content);

protected:
  QString dir;
  QMap<QString, QString> cache;
};

