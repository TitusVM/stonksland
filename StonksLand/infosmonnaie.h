#ifndef INFOSMONNAIE_H
#define INFOSMONNAIE_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>

#include "api.h"
#include "cache.h"
#include "currency.h"
#include "exchangerate.h"
#include "getinfo.h"
#include "graph.h"

class infosMonnaie : public QWidget
{
    Q_OBJECT

public:
    infosMonnaie(GetInfo const* infos);
    ~infosMonnaie();

    void setInfos(QString country, QString currency, QString symbol, QString iso);

public slots:
    void showMarkets();
    void showCryptos();

private:
    QLineEdit *country;
    QLineEdit *currency;
    QLineEdit *symbol;
    QLineEdit *ISO;
    QLabel *countryFlagLabel;
    QPushButton *showIndices;
    QPushButton *showCrypto;
    ExchangeRate *exchRate;
    Graph *graph;
    Cache cacheCurrent;
    Cache cacheHistorical;
    Api api;
    QWidget *stockWindow;
    QWidget *cryptoWindow;
    GetInfo const* infos;
};
#endif // INFOSMONNAIE_H
