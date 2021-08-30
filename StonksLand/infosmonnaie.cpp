#include "infosmonnaie.h"
#include "currencyexchanger.h"

infosMonnaie::infosMonnaie(QWidget *parent): QWidget(parent),
  cacheCurrent("cache/current"), cacheHistorical("cache/historical", INT_MAX), api("d5bbf30a2178fbd92e5af9ae731531fc")
{
    if (!cacheCurrent.contains("current")) {
        cacheCurrent.add("current", api.dl());
    }

    QDate date = QDate(QDate::currentDate().year(), 12, 31);
    if (date > QDate::currentDate()) {
        date = date.addYears(-1);
    }

    for (int i = 0; i < 20; ++i, date = date.addYears(-1)) {
        QString y = QString::number(date.year());
        if (!cacheHistorical.contains(y)) {
            cacheHistorical.add(y, api.dl(date));
        }
    }

    this->resize(1000,200);
    country = new QLineEdit;
    currency = new QLineEdit;
    symbol = new QLineEdit;
    ISO = new QLineEdit;
    exchRate = new ExchangeRate;
    graph = new Graph;

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

    grid->addWidget(countryLabel, 0, 0, 1, 1);
    grid->addWidget(currencyLabel, 1, 0, 1, 2);
    grid->addWidget(symbolLabel, 2, 0, 1, 2);
    grid->addWidget(ISOLabel, 3, 0, 1, 2);
    grid->addWidget(countryFlagLabel, 0, 1);
    grid->addWidget(country, 0, 2);
    grid->addWidget(currency, 1, 2);
    grid->addWidget(symbol, 2, 2);
    grid->addWidget(ISO, 3, 2);
    grid->addWidget(exchRate, 0, 3, 4, 1);
    grid->addWidget(currExch, 0, 4, 4, 1);
    grid->addWidget(graph, 0, 5, 5, 1);


    setLayout(grid);
}

void infosMonnaie::setInfos(QString country, QString currency, QString symbol, QString iso) {
    this->country->setText(country);
    this->currency->setText(currency);
    this->symbol->setText(symbol);
    this->ISO->setText(iso);

    this->exchRate->updateRate(iso);

    QDate date = QDate(QDate::currentDate().year(), 12, 31);
    if (date > QDate::currentDate()) {
        date = date.addYears(-1);
    }
    QLineSeries *series = new QLineSeries;
    for (int i = 0; i < 20; ++i, date = date.addYears(-1)) {
        QString y = QString::number(date.year());
        QMap<QString, double> rates = Api::extractRates(cacheHistorical.get(y));
        *series << QPointF(date.endOfDay().toMSecsSinceEpoch(), rates[iso]);
    }
    this->graph->display(currency, series);

    QPixmap countryFlag("://data/flags/" + country.replace(' ', '_') + ".png");
    countryFlagLabel->setPixmap(countryFlag);
}

infosMonnaie::~infosMonnaie()
{
}

