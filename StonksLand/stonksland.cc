#include "stonksland.h"

#include <QApplication>
#include <QDesktopServices>
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
  infos = new GetInfo("://data/csv_combined.csv");
  std::vector<Currency> currencies = infos->getCurrencyList();

  Map *map = new Map;

  infosMonnaie *infoBox = new infosMonnaie(currencies);

  List *list = new List(currencies);
  QSizePolicy sp = list->sizePolicy();
  sp.setHorizontalPolicy(QSizePolicy::Maximum);
  list->setSizePolicy(sp);

  QMenu* fileMenu = new QMenu("File");
  fileMenu->addAction("Quit", qApp, &QApplication::quit, QKeySequence("Ctrl+Q"));

  QMenu* aboutMenu = new QMenu("About");
  aboutMenu->addAction("About exchangeratesapi.io", []() {
    QDesktopServices::openUrl(QUrl("https://exchangeratesapi.io/about/"));
  });
  aboutMenu->addAction("About Qt", [this]() {
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

  setLayout(vlayout);

  connect(list, &List::currentItemChanged, [=](QListWidgetItem *current) {
    Currency currency = infos->findCurrency(current->text());
    std::vector<Country> countries = infos->findCountries(currency);
    QString strCountries = "";

    emit map->reset();
    for (Country country : countries) {
      strCountries += country.getName() + ", ";
      emit map->highlight(country.getName());
    }

    strCountries = strCountries.left(strCountries.length() - 2);
    infoBox->setInfos(strCountries, currency.getName(), currency.getSymbol(), currency.getISO());
  });

  connect(map, &Map::countryClicked, [=](QString countryName) {
    Currency currency = infos->findCurrency(infos->findCountry(countryName));
    infoBox->setInfos(countryName, currency.getName(), currency.getSymbol(), currency.getISO());
    emit map->reset();
    emit map->highlight(countryName);
    QListWidgetItem* item = list->findItems(currency.getName(), Qt::MatchExactly)[0];
    item->setSelected(true);
    list->scrollToItem(item);
  });
}

StonksLand::~StonksLand()
{
  delete infos;
}
