#ifndef STOCK_MARKET_H
#define STOCK_MARKET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QJsonDocument>
#include <QListWidget>

#include "cache.h"
#include "graph.h"

class StockMarket : public Graph
{
    Q_OBJECT

public:
    StockMarket(QString marketIndex, QString key);
    ~StockMarket();

    void compute(QString, QString);

protected slots:
    void slotNetwManager();

private:
    Cache cache;
    QString marketIndex;

};
#endif // CurrencyExchanger_H
