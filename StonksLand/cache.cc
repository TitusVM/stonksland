#include "cache.h"

#include <cstdio>
#include <stdexcept>

#include <QDateTime>
#include <QDir>
#include <QFileInfo>

Cache::Cache(QString directory, int validity): dir(directory), cache() {
  if (!QDir(directory).exists()) {
    QDir().mkpath(directory);
  }

  QStringList files = QDir(directory).entryList(QDir::Filter::Files);
  QDateTime now = QDateTime::currentDateTime();

  for (QString file : files) {
    QString path = QDir::cleanPath(directory + "/" + file);
    QDateTime date = QFileInfo(path).lastModified();
    if (date.addSecs(validity) > now) {
      QFile f(path);
      f.open(QFile::ReadOnly);
      QString content = QString(f.readAll());
      cache.insert(file, content);
    }
  }
}

bool Cache::contains(QString name) {
  return cache.contains(name);
}

QString Cache::get(QString name) {
  if (!contains(name)) {
    throw std::logic_error("Can't read non-existing cache.");
  }

  return cache[name];
}

void Cache::add(QString name, QString content) {
  cache.insert(name, content);
  QFile file(QDir::cleanPath(dir + "/" + name));
  file.open(QFile::WriteOnly);
  file.write(content.toUtf8());
}
