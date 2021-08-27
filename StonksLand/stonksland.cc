#include "stonksland.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "infosmonnaie.h"
#include "list.h"
#include "map.h"

StonksLand::StonksLand(QWidget *parent)
  : QWidget(parent)
{
  infos = new GetInfo("C:/Users/luan.coroli/Downloads/csv_combined.csv");

  Map *map = new Map;
  infosMonnaie *infoBox = new infosMonnaie;
  QSizePolicy sp = infoBox->sizePolicy();
  sp.setVerticalPolicy(QSizePolicy::Maximum);
  infoBox->setSizePolicy(sp);
  List *list = new List;
  sp = list->sizePolicy();
  sp.setHorizontalPolicy(QSizePolicy::Maximum);
  list->setSizePolicy(sp);

  QVBoxLayout *vlayout = new QVBoxLayout;
  vlayout->addWidget(map);
  vlayout->addWidget(infoBox);

  QHBoxLayout *hlayout = new QHBoxLayout;
  hlayout->addWidget(list);
  hlayout->addLayout(vlayout);

  setLayout(hlayout);


  connect(map, &Map::countryClicked, [=](QString countryName) {
    Currency currency = infos->findCurrency(infos->findCountry(countryName));
    infoBox->setInfos(countryName, currency.getName(), currency.getSymbol(), currency.getISO());
    emit map->reset();
    emit map->highlight(countryName);
    QListWidgetItem* item = list->findItems(currency.getName(), Qt::MatchExactly)[0];
    item->setSelected(true);
    list->scrollToItem(item);
  });

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
}

StonksLand::~StonksLand()
{
  delete infos;
}

