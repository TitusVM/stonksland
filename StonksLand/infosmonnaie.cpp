#include <QCoreApplication>
#include <QEventLoop>

#include "infosmonnaie.h"
#include "currencyexchanger.h"
#include "stockmarket.h"

infosMonnaie::infosMonnaie(GetInfo const* infos): QWidget(),
  cacheCurrent("cache/current"), cacheHistorical("cache/historical", INT_MAX), api(infos->getExchangeratesapiApiKey()), infos(infos)
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

    QMap<QString, double> currentRates = Api::extractRates(cacheCurrent.get("current"));

    this->resize(1000,200);
    country = new QLineEdit;
    country->setReadOnly(true);
    currency = new QLineEdit;
    currency->setReadOnly(true);
    symbol = new QLineEdit;
    symbol->setReadOnly(true);
    ISO = new QLineEdit;
    ISO->setReadOnly(true);
    exchRate = new ExchangeRate(currentRates);
    graph = new Graph;

    QLabel *countryLabel = new QLabel;
    countryLabel->setText("Country");
    QLabel *currencyLabel = new QLabel;
    currencyLabel->setText("Currency");
    QLabel *symbolLabel = new QLabel;
    symbolLabel->setText("Symbol or local name");
    QLabel *ISOLabel = new QLabel;
    ISOLabel->setText("ISO Code");

    QLabel *copyright = new QLabel;
    QFont f( "Arial", 8, true);
    copyright->setFont(f);
    copyright->setStyleSheet("color:grey;");
    copyright->setText("  Quotes by exchangeratesapi.io");

    countryFlagLabel = new QLabel;
    countryFlagLabel->setText("");
    countryFlagLabel->setStyleSheet("margin-left:140px;");

    /* Display markets ://data/icon/stock.png */
    showIndices = new QPushButton;
    showIndices->setIcon(QIcon("://data/icons/stock.png"));
    showIndices->setText("Display live markets");
    showIndices->setStyleSheet("background: #009900; color: white; margin-left: 230px;");

    connect(showIndices, SIGNAL(clicked()), this, SLOT(showMarkets()));

    exchRate->resize(150,100);

    QFont f2( "Arial", 18, true);
    showIndices->setFont(f2);


    QGridLayout *grid = new QGridLayout;

    CurrencyExchanger *currExch = new CurrencyExchanger(currentRates, infos->getCurrencyList());

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
    grid->addWidget(copyright, 4, 3, 1, 3);
    grid->addWidget(showIndices, 4, 4, 1, 1);


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
    this->graph->display(currency, series, "yyyy", true);  // takes ownership of series

    QPixmap countryFlag("://data/flags/" + country.replace(' ', '_') + ".png");
    countryFlagLabel->setPixmap(countryFlag);
}

void infosMonnaie::showMarkets()
{
    QString apiKey = infos->getMarketstackApiKey();

    QHBoxLayout *stockHBoxTop = new QHBoxLayout;
    QHBoxLayout *stockHBoxBot = new QHBoxLayout;
    QHBoxLayout *stockHBoxCopyright = new QHBoxLayout;
    QVBoxLayout *stockVBox = new QVBoxLayout;
    stockWindow = new QWidget(this, Qt::Window);
    stockWindow->setAttribute(Qt::WA_DeleteOnClose);
    StockMarket *stockDAX = new StockMarket("DAX", apiKey);
    StockMarket *stockNASDAQ = new StockMarket("NDAQ", apiKey);
    StockMarket *stockSMIC = new StockMarket("0981.XHKG", apiKey);
    StockMarket *stockGOOG = new StockMarket("GOOGL", apiKey);

    QLabel *copyright = new QLabel;
    QFont f( "Arial", 8, true);
    copyright->setFont(f);
    copyright->setStyleSheet("color:grey;");
    copyright->setText("  Quotes by api.marketstack.com");

    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    StockMarket *stockINTC = new StockMarket("INTC", apiKey);
    StockMarket *stockMSFT = new StockMarket("MSFT", apiKey);
    StockMarket *stockAAPL = new StockMarket("AAPL", apiKey);
    StockMarket *stockNOK = new StockMarket("NOK", apiKey);

    stockHBoxTop->addWidget(stockDAX);
    stockHBoxTop->addWidget(stockNASDAQ);
    stockHBoxTop->addWidget(stockSMIC);
    stockHBoxTop->addWidget(stockGOOG);

    stockHBoxBot->addWidget(stockINTC);
    stockHBoxBot->addWidget(stockMSFT);
    stockHBoxBot->addWidget(stockAAPL);
    stockHBoxBot->addWidget(stockNOK);

    stockHBoxCopyright->addWidget(copyright);

    stockVBox->addLayout(stockHBoxTop);
    stockVBox->addLayout(stockHBoxBot);
    stockVBox->addLayout(stockHBoxCopyright);

    stockWindow->setLayout(stockVBox);
    stockWindow->show();
}

infosMonnaie::~infosMonnaie()
{
}

