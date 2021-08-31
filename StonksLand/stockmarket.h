#ifndef STOCK_MARKET_H
#define STOCK_MARKET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QListWidget>
#include "graph.h"



class StockMarket : public Graph
{
    Q_OBJECT

public:
    StockMarket(QWidget *parent = nullptr, QString marketIndex = "AAPL");
    ~StockMarket();
    void compute(QString, QString);

protected slots:
    void slotNetwManager(QNetworkReply*);

private:

    QJsonDocument *json_list;
    QNetworkRequest *request;
    QByteArray *reply_data;
    QString *marketIndex;

};
#endif // CurrencyExchanger_H
