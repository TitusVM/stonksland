#ifndef INFOSMONNAIE_H
#define INFOSMONNAIE_H

#include <vector>

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>

#include "api.h"
#include "cache.h"
#include "currency.h"
#include "exchangerate.h"
#include "graph.h"

class infosMonnaie : public QWidget
{
    Q_OBJECT

public:
    infosMonnaie(std::vector<Currency> const& currencies);
    ~infosMonnaie();

    void setInfos(QString country, QString currency, QString symbol, QString iso);

private:
    QLineEdit *country;
    QLineEdit *currency;
    QLineEdit *symbol;
    QLineEdit *ISO;
    QLabel *countryFlagLabel;
    ExchangeRate *exchRate;
    Graph *graph;
    Cache cacheCurrent;
    Cache cacheHistorical;
    Api api;
};
#endif // INFOSMONNAIE_H
