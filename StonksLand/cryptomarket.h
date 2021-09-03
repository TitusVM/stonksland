#ifndef CRYPTOMARKET_H
#define CRYPTOMARKET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QJsonDocument>
#include <QListWidget>

#include "cache.h"
#include "graph.h"

class CryptoMarket : public Graph
{
    Q_OBJECT

public:
    CryptoMarket(QString cryptoIndex = "ETH");
    ~CryptoMarket();
    void compute(QString, QString);

protected slots:
    void slotNetwManager();

private:
    Cache cache;
    QString cryptoIndex;
    int numberOfDays;

};

#endif // CRYPTOMARKET_H
