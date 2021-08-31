#ifndef CURRENCY_EXCHANGER_H
#define CURRENCY_EXCHANGER_H

#include <vector>

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QMap>

#include "currency.h"

class CurrencyExchanger : public QWidget
{
    Q_OBJECT

public:
    CurrencyExchanger(QMap<QString, double> const& rates, std::vector<Currency> const& currencies);
    ~CurrencyExchanger();
    void compute(QString, QString);

protected slots:
    void convert(int);
    void convert(QString);

private:
    QLabel *valueUnit;
    QLineEdit *resultConv;
    QComboBox *comboListA;
    QComboBox *comboListB;
    QLineEdit *valueConv;
    QMap<QString, double> rates;
};
#endif // CurrencyExchanger_H
