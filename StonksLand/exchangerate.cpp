#include "exchangerate.h"

#include <stdlib.h>
#include <cmath>

#include <QEventLoop>
#include <QMap>


//#include <QDebug>

ExchangeRate::ExchangeRate(QMap<QString, double> const& rates)
    : QWidget(), rates(rates)
{
    layout = new QGridLayout;
    exchangeRate = new QLabel;
    title = new QLabel;
    title->setText("Exchange rate from AFN to EUR");
    QFont f( "Arial", 10, QFont::Bold);
    title->setFont(f);
}

void ExchangeRate::updateRate(QString iso)
{
    /* Iterate list and find currency rate with currency symbol */
    for (QString const& key : rates.keys())
    {
        if(key == iso)
        {
            double valueDouble = ceil(rates[key] * 100.0) / 100.0;
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
