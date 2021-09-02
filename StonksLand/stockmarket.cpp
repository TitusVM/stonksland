#include "stockmarket.h"

#include <cmath>

#include <QDateTime>
#include <QDebug>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

StockMarket::StockMarket(QWidget*, QString marketIndex)
    : Graph(), cache("cache/stocks"), marketIndex(marketIndex)
{
    if (!cache.contains(marketIndex)) {
      qDebug() << "Cache for" << marketIndex << "outdated, updating...";
      QNetworkRequest request;
      QNetworkAccessManager nam;

      QEventLoop loop;
      QObject::connect(&nam, SIGNAL(finished(QNetworkReply*)),
                       &loop,
                       SLOT(quit()));

      /* Response json readAll */
      request.setUrl(QUrl("http://api.marketstack.com/v1/eod?access_key=67bfbdb0d61ec2fb08a7f34b6d1f7b32&symbols=" + marketIndex));
      QNetworkReply *reply = nam.get(request);  // reply is owned by nam
      loop.exec();

      if (reply->error())
      {
          qDebug() << reply->errorString();
          return;
      }

      cache.add(marketIndex, reply->readAll());
    }

    slotNetwManager();
}

void StockMarket::slotNetwManager()
{
    QJsonDocument json_list = QJsonDocument::fromJson(cache.get(marketIndex).toUtf8());
    QJsonObject json_object = json_list.object();
    QJsonValue json_value = json_object.value("data");
    QLineSeries *rates = new QLineSeries;

    for(int i = 0; i < 100; i++)
    {
        *rates <<QPointF(QDateTime::fromString(json_value[i].toObject()["date"].toString(),
                         Qt::ISODate).toMSecsSinceEpoch(),
                        json_value[i].toObject()["close"].toDouble()
                        );

    }
    display(this->marketIndex, rates, "dd-MM", false);  // takes ownership of rates
}

StockMarket::~StockMarket()
{
}

