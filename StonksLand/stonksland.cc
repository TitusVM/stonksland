#include "stonksland.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "infosmonnaie.h"
#include "list.h"
#include "map.h"
#include "getinfo.h"

StonksLand::StonksLand(QWidget *parent)
  : QWidget(parent)
{
  GetInfo infos("");

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


  connect(map, &Map::countryClicked, [&](QString countryName) {
    Currency currency = infos.findCurrency(infos.findCountry(countryName));
    infoBox->setInfos(countryName, currency.getName(), currency.getSymbol(), currency.getISO());
    emit map->reset();
    emit map->highlight(countryName);
  });
}

StonksLand::~StonksLand()
{
}

