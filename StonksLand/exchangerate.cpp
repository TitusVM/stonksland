#include "exchangerate.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <stdlib.h>
#include <cmath>

#include <QEventLoop>


//#include <QDebug>

ExchangeRate::ExchangeRate(QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout;
    exchangeRate = new QLabel;
    title = new QLabel;
    title->setText("Exchange rate from AFN to EUR");
    QFont f( "Arial", 10, QFont::Bold);
    title->setFont(f);
    json_list = new QJsonValue;

    QNetworkAccessManager *nam = new QNetworkAccessManager;
    QNetworkRequest *request = new QNetworkRequest;


    /* Currency base change only in API premium plan */
    QUrl apiUrl;
    apiUrl = "http://api.exchangeratesapi.io/v1/latest?access_key=d5bbf30a2178fbd92e5af9ae731531fc";
    request->setUrl(apiUrl);

    QNetworkReply *reply = nam->post(*request, "");

    /* EventLoop until reply comes in */
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    /* Response json readAll */
    QByteArray response_data = reply->readAll();
    QJsonDocument *json_response_data = new QJsonDocument;
    *json_response_data = QJsonDocument::fromJson(response_data);
    reply->deleteLater();

    /* Turn into object and then into value list (ignore headers) */
    QJsonObject json_object = json_response_data->object();
    *json_list = json_object.value("rates");

}

void ExchangeRate::updateRate(QString iso)
{
    iso.remove("\r\n");
    /* Iterate list and find currency rate with currency symbol */
    foreach(const QString& key, json_list->toObject().keys())
    {
        if(key == iso)
        {
            QJsonValue value = json_list->toObject().value(iso);
            double valueDouble = ceil(value.toDouble() * 100.0) / 100.0;
            QString strValue = QString::number(valueDouble);
            this->exchangeRate->setText("  1 EUR = " + strValue + " " + iso);
            title->setText("Exchange rate from " + iso + " to EUR");
            /* For DEBUG purposes */
            //qDebug() << "Key = " << currencySymbol << ", Value = " << strValue;
        }
    }
    exchangeRate->setStyleSheet(
                                "boarder-style: solid;"
                                "color: white;"
                                "background: grey;"
                                );
    QFont f2("Arial", 15, QFont::Bold);
    exchangeRate->setAlignment(Qt::AlignmentFlag::AlignVCenter);
    exchangeRate->setFont(f2);
    layout->addWidget(title, 0,0);
    layout->addWidget(exchangeRate, 1,0);
    setLayout(layout);
}


ExchangeRate::~ExchangeRate()
{
}
