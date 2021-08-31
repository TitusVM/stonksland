#include "stockmarket.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLineEdit>
#include <cmath>

#include <QDebug>

#include <QEventLoop>

#include <QDateTime>
#include <QUrl>
#include <QLayout>
#include <QListWidget>

StockMarket::StockMarket(QWidget *parent, QString marketIndex)
    : Graph()
{
    this->marketIndex = new QString;
    (*this->marketIndex) = marketIndex;
    request = new QNetworkRequest;
    QNetworkAccessManager *nam = new QNetworkAccessManager;

    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this,
                     SLOT(slotNetwManager(QNetworkReply*)));

    /* Response json readAll */
    request->setUrl(QUrl("http://api.marketstack.com/v1/eod?access_key=67bfbdb0d61ec2fb08a7f34b6d1f7b32&symbols=" + (*this->marketIndex)));
    nam->get(*request);
}

void StockMarket::slotNetwManager(QNetworkReply *reply)
{
    reply_data = new QByteArray;
    json_list = new QJsonDocument;

    if (reply->error())
    {
        qDebug() << reply->errorString();
        return;
    }
    *reply_data = reply->readAll();
    *json_list = QJsonDocument::fromJson(*reply_data);
    QJsonObject json_object = json_list->object();
    QJsonValue *json_value = new QJsonValue;
    *json_value = json_object.value("data");

    QLineSeries *rates = new QLineSeries;

    for(int i = 0; i < 100; i++)
    {
        *rates <<QPointF(QDateTime::fromString((*json_value)[i].toObject()["date"].toString(),
                         Qt::ISODate).toMSecsSinceEpoch(),
                        (*json_value)[i].toObject()["close"].toDouble()
                        );

    }
    display((*this->marketIndex), rates, "dd-MM", false);


}

StockMarket::~StockMarket()
{
}

