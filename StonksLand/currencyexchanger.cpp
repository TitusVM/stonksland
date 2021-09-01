#include "currencyexchanger.h"

#include <QLineEdit>
#include <cmath>

#include <QDebug>

#include <QEventLoop>
#include <QUrl>
#include <QLayout>

CurrencyExchanger::CurrencyExchanger(QMap<QString, double> const& rates, std::vector<Currency> const& currencies)
    : QWidget(), rates(rates)
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


    for (Currency const& curr : currencies)
    {
        comboListA->addItem(curr.getISO());
        comboListB->addItem(curr.getISO());
    }

    connect(comboListA, SIGNAL(currentIndexChanged(int)), this, SLOT(convert(int)));
    connect(comboListB, SIGNAL(currentIndexChanged(int)), this, SLOT(convert(int)));

    comboListA->model()->sort(0);
    comboListA->setCurrentIndex(27);
    valueUnit->setText("CHF");
    comboListB->model()->sort(0);
    comboListB->setCurrentIndex(42);
    resultConv->setText("0 EUR");

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

void CurrencyExchanger::convert(int)
{
    compute(comboListA->currentText(),comboListB->currentText());
}

void CurrencyExchanger::convert(QString)
{
    compute(comboListA->currentText(),comboListB->currentText());
}


void CurrencyExchanger::compute(QString currencyA, QString currencyB)
{
    /* Conversion from currency1 to currency2 through EUR */
    double currencyEurtoB = rates[currencyB];
    double currencyEurtoA = rates[currencyA];

    double valueToExchange = valueConv->text().toDouble();

    double eurValueCurrA = valueToExchange/currencyEurtoA;
    double eurValueCurrB = eurValueCurrA*currencyEurtoB;
    double valueDouble = ceil(eurValueCurrB * 100.0) / 100.0;

    resultConv->setText(QString::number(valueDouble) + " " + currencyB);
    valueUnit->setText(currencyA);
}

CurrencyExchanger::~CurrencyExchanger()
{
}

