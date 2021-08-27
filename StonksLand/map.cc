#include "map.h"

#include "maprender.h"

#include <QSlider>
#include <QVBoxLayout>
#include <QWebChannel>
#include <QWheelEvent>

#include <QMessageBox>

Map::Map(QWidget* parent): QWidget(parent)
{
  mapRender = new MapRender(this);
  QVBoxLayout *layout = new QVBoxLayout;
  setLayout(layout);
  layout->addWidget(mapRender);
  layout->setMargin(0);

  mapRender->installEventFilter(this);
  mapRender->setFocusPolicy(Qt::StrongFocus);
}

void Map::highlight(QString country) {
  emit mapRender->highlightJs(country);
}

void Map::reset() {
  emit mapRender->resetJs();
}
