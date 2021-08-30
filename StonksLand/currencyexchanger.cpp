#include "currencyexchanger.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLineEdit>
#include <cmath>

#include <QDebug>

#include <QEventLoop>
#include <QUrl>
#include <QLayout>

CurrencyExchanger::CurrencyExchanger(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *hLayoutTop = new QHBoxLayout;
    QHBoxLayout *hLayoutBot = new QHBoxLayout;
    QVBoxLayout *vLayout = new QVBoxLayout;

    comboListA = new QComboBox;
    comboListB = new QComboBox;

    valueConv = new QLineEdit;
    valueConv->setFixedWidth(120);
    valueConv->setText("0.0");
    valueConv->setAlignment(Qt::AlignmentFlag::AlignRight);
    valueConv->setValidator( new QDoubleValidator(0, 0, 2, this) );

    connect(valueConv, SIGNAL(textChanged(QString)), this, SLOT(convert(QString)));

    valueUnit = new QLabel;

    QLabel *resultLabel = new QLabel;
    resultLabel->setText("After Conversion:");

    resultConv = new QLineEdit;
    resultConv->setReadOnly(true);
    resultConv->setFixedWidth(120);
    resultConv->setAlignment(Qt::AlignmentFlag::AlignRight);
    resultConv->setStyleSheet(
                              "color: white;"
                              "background: grey;"
                             );
    resultConv->setText("0,0");

    QNetworkAccessManager *nam = new QNetworkAccessManager;
    QNetworkRequest *request = new QNetworkRequest;
    json_list = new QJsonValue;


    /* Currency base change only in API premium plan */
    request->setUrl(QUrl("http://api.exchangeratesapi.io/v1/latest?access_key=d5bbf30a2178fbd92e5af9ae731531fc"));
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

    foreach(const QString& key, json_list->toObject().keys())
    {
        comboListA->addItem(key);
        comboListB->addItem(key);
    }

    connect(comboListA, SIGNAL(currentIndexChanged(int)), this, SLOT(convert(int)));
    connect(comboListB, SIGNAL(currentIndexChanged(int)), this, SLOT(convert(int)));

    hLayoutTop->addWidget(comboListA);
    hLayoutTop->addWidget(comboListB);
    hLayoutBot->addWidget(valueConv);
    hLayoutBot->addWidget(valueUnit);
    hLayoutBot->addWidget(resultLabel);
    hLayoutBot->addWidget(resultConv);
    vLayout->addLayout(hLayoutTop);
    vLayout->addLayout(hLayoutBot);

    setLayout(vLayout);
}

void CurrencyExchanger::convert(int index)
{
    compute(comboListA->currentText(),comboListB->currentText());
}

void CurrencyExchanger::convert(QString string)
{
    compute(comboListA->currentText(),comboListB->currentText());
}


void CurrencyExchanger::compute(QString currencyA, QString currencyB)
{
    /* Conversion from currency1 to currency2 through EUR */
    QJsonValue currencyEurtoB;
    QJsonValue currencyEurtoA;

    double valueToExchange = valueConv->text().toDouble();

    foreach(const QString& key, json_list->toObject().keys())
    {
        if(key == currencyA) currencyEurtoA = json_list->toObject().value(currencyA);
        if(key == currencyB) currencyEurtoB = json_list->toObject().value(currencyB);
    }

    double doubCurrencyEurtoA = currencyEurtoA.toDouble();
    double doubCurrencyEurtoB = currencyEurtoB.toDouble();

    double eurValueCurrA = valueToExchange/doubCurrencyEurtoA;
    double eurValueCurrB = eurValueCurrA*doubCurrencyEurtoB;
    double valueDouble = ceil(eurValueCurrB * 100.0) / 100.0;

    resultConv->setText(QString::number(valueDouble) + " " + currencyB);
    valueUnit->setText(currencyA);
}

CurrencyExchanger::~CurrencyExchanger()
{
}

