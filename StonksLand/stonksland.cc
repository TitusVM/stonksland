#include "stonksland.h"

#include <QApplication>
#include <QDesktopServices>
#include <QDir>
#include <QHBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>

#include "infosmonnaie.h"
#include "list.h"
#include "map.h"
#include "stockmarket.h"

StonksLand::StonksLand(QWidget *parent)
  : QWidget(parent)
{
  infos = new GetInfo("://data/csv_combined.csv", "keys.txt");
  if (infos->getExchangeratesapiApiKey() == "" || infos->getMarketstackApiKey() == "") {
    QString here = QDir().absolutePath();
    QMessageBox::critical(
          nullptr,  // no parent so the window is in the taskbar
          "Missing api keys",
          "The keys for the web apis couldn't be found.<br>"
          "Please create a file called \"keys.txt\" in <a href=\"" + here + "\">the app's directory</a> and put the keys inside.<br><br>"
          "Put the api key for <a href=\"https://exchangeratesapi.io\">exchangeratesapi.io</a>,<br>"
          "Then on a new line, the api key for <a href=\"https://marketstack.com\">marketstack.com</a>.");
    QMetaObject::invokeMethod(this, "close", Qt::QueuedConnection);
    return;
  }

  Map *map = new Map;

  infosMonnaie *infoBox = new infosMonnaie(infos);

  List *list = new List(infos->getCurrencyList());
  QSizePolicy sp = list->sizePolicy();
  sp.setHorizontalPolicy(QSizePolicy::Maximum);
  list->setSizePolicy(sp);

  QMenu* fileMenu = new QMenu("File");
  fileMenu->addAction("Quit", qApp, &QApplication::quit, QKeySequence("Ctrl+Q"));

  QMenu* aboutMenu = new QMenu("About");
  aboutMenu->addAction("About exchangeratesapi.io", this, []() {
    QDesktopServices::openUrl(QUrl("https://exchangeratesapi.io/about/"));
  });
  aboutMenu->addAction("About Qt", this, [this]() {
    QMessageBox::aboutQt(this);
  });

  QMenuBar *bar = new QMenuBar;
  bar->addMenu(fileMenu);
  bar->addMenu(aboutMenu);

  QHBoxLayout *hlayout = new QHBoxLayout;
  hlayout->addWidget(list);
  hlayout->addWidget(map);

  QVBoxLayout *vlayout = new QVBoxLayout;
  vlayout->addLayout(hlayout);
  vlayout->addWidget(infoBox);
  vlayout->setMenuBar(bar);

  connect(list, &List::currentItemChanged, this, [=](QListWidgetItem *current) {
    Currency currency = infos->findCurrency(current->text());
    std::vector<Country> countries = infos->findCountries(currency);
    QString strCountries = "";

    map->reset();
    for (const Country &country : qAsConst(countries)) {
      strCountries += country.getName() + ", ";
      map->highlight(country.getName());
    }

    strCountries = strCountries.left(strCountries.length() - 2);
    infoBox->setInfos(strCountries, currency.getName(), currency.getSymbol(), currency.getISO());
  });

  connect(map, &Map::countryClicked, [=](QString countryName) {
    Currency currency = infos->findCountry(countryName).getCurrency();
    infoBox->setInfos(countryName, currency.getName(), currency.getSymbol(), currency.getISO());
    map->reset();
    map->highlight(countryName);
    QListWidgetItem* item = list->findItems(currency.getName(), Qt::MatchExactly).at(0);
    item->setSelected(true);
    list->scrollToItem(item);
  });

  list->setCurrentRow(0);

  setLayout(vlayout);
}

StonksLand::~StonksLand()
{
  delete infos;
}
