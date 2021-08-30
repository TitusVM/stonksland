#include "infosmonnaie.h"
#include "currencyexchanger.h"

infosMonnaie::infosMonnaie(QWidget *parent)
    : QWidget(parent)
{
    this->resize(1000,200);
    country = new QLineEdit;
    currency = new QLineEdit;
    symbol = new QLineEdit;
    ISO = new QLineEdit;
    exchRate = new ExchangeRate;

    QLabel *countryLabel = new QLabel;
    countryLabel->setText("Country");
    QLabel *currencyLabel = new QLabel;
    currencyLabel->setText("Currency");
    QLabel *symbolLabel = new QLabel;
    symbolLabel->setText("Symbol or local name");
    QLabel *ISOLabel = new QLabel;
    ISOLabel->setText("ISO Code");

    countryFlagLabel = new QLabel;
    countryFlagLabel->setText("");
    countryFlagLabel->setStyleSheet("margin-left:140px;");

    //QPixmap currencyPicture(":/truc/machin/non.png");
    exchRate->resize(150,100);


    QGridLayout *grid = new QGridLayout;
    CurrencyExchanger *currExch = new CurrencyExchanger;
    grid->addWidget(countryLabel,0,0,1,4);
    grid->addWidget(currencyLabel,1,0,1,2);
    grid->addWidget(symbolLabel,2,0,1,2);
    grid->addWidget(ISOLabel,3,0,1,2);
    grid->addWidget(countryFlagLabel,0,0,1,1, Qt::AlignmentFlag::AlignRight);
    grid->addWidget(country,0,1,1,2);
    grid->addWidget(currency,1,1,1,2);
    grid->addWidget(symbol,2,1,1,2);
    grid->addWidget(ISO,3,1,1,2);
    grid->addWidget(exchRate,0,3,4,1);
    grid->addWidget(currExch, 0,5,4,2);

    setLayout(grid);
}

void infosMonnaie::setInfos(QString country, QString currency, QString symbol, QString iso) {
    this->country->setText(country);
    this->currency->setText(currency);
    this->symbol->setText(symbol);
    this->ISO->setText(iso);
    this->exchRate->updateRate(iso);

    QPixmap countryFlag("://data/flags/" + country.replace(' ', '_') + ".png");
    countryFlagLabel->setPixmap(countryFlag);
}

infosMonnaie::~infosMonnaie()
{
}

