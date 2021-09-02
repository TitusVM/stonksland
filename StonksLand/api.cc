#include "api.h"

#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

Api::Api(QString key): key(key)
{
}

QString Api::dl() {
  QEventLoop loop;
  QNetworkAccessManager manager;
  QObject::connect(&manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
  QNetworkRequest request;
  request.setUrl(QUrl("http://api.exchangeratesapi.io/v1/latest?access_key=" + key + "&base=EUR"));
  QNetworkReply* reply = manager.get(request);  // reply is owned by manager
  loop.exec();
  QString answer = reply->readAll();
  return answer;
}

QString Api::dl(QDate date) {
  QEventLoop loop;
  QNetworkAccessManager manager;
  QObject::connect(&manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
  QNetworkRequest request;
  request.setUrl(QUrl("http://api.exchangeratesapi.io/v1/" + date.toString("yyyy-MM-dd") + "?access_key=" + key + "&base=EUR"));
  QNetworkReply* reply = manager.get(request);  // reply is owned by manager
  loop.exec();
  QString answer = reply->readAll();
  return answer;
}

QMap<QString, double> Api::extractRates(QString json) {
  QJsonDocument jdoc = QJsonDocument::fromJson(json.toUtf8());
  QMap<QString, double> rates;
  QJsonObject jobjRates = jdoc["rates"].toObject();
  QJsonObject::iterator it = jobjRates.begin();
  for (; it != jobjRates.end(); ++it) {
    rates.insert(it.key(), it->toDouble());
  }

  return rates;
}
