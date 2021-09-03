#include "cryptomarket.h"

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

CryptoMarket::CryptoMarket(QString cryptoIndex)
    : Graph(), cache("cache/stocks"), cryptoIndex(cryptoIndex)
{
    static QString APIKEY = "b7c867610407f5a1df967a59cfbee7b148c7c11e";
    static QDateTime endTime = QDateTime::currentDateTime();
    numberOfDays = 365;

    static QDateTime startTime = endTime.addDays(-numberOfDays);

    static QString strEndTime = endTime.toString("yyyy-MM-ddThh:mm:ssZ");
    static QString strStartTime = startTime.toString("yyyy-MM-ddThh:mm:ssZ");

    if (!cache.contains(cryptoIndex)) //changed !
    {
      qDebug() << "Cache for" << cryptoIndex << "outdated, updating...";
      QNetworkRequest *request = new QNetworkRequest;
      QNetworkAccessManager *nam = new QNetworkAccessManager;

      QEventLoop loop;
      QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                       &loop,
                       SLOT(quit()));

      /* Response json readAll */
      request->setUrl(QUrl("http://api.nomics.com/v1/exchange-rates/history?key=" + APIKEY + "&start=" + strStartTime + "&end=" + strEndTime + "&currency=" + cryptoIndex));
      QNetworkReply *reply = nam->get(*request);
      loop.exec();

      if (reply->error())
      {
          qDebug() << reply->errorString();
          return;
      }

      cache.add(cryptoIndex, reply->readAll());
    }

    slotNetwManager();
}

void CryptoMarket::slotNetwManager()
{
    QJsonDocument json_list = QJsonDocument::fromJson(cache.get(cryptoIndex).toUtf8());
    QLineSeries *rates = new QLineSeries;
    for(int i = 0; i < numberOfDays; i++)
    {
        *rates <<QPointF(QDateTime::fromString(json_list[i].toObject()["timestamp"].toString(),
                         Qt::ISODate).toMSecsSinceEpoch(),
                        json_list[i].toObject()["rate"].toString().toDouble()
                        );
    }
    display(this->cryptoIndex, rates, "dd-MM-yy", false);
}

CryptoMarket::~CryptoMarket()
{
}
