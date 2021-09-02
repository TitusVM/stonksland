#include "maprender.h"

#include "map.h"

#include <QWebChannel>

MapRender::MapRender(QWidget *parent):
  QWebEngineView(parent)
{
  QWebChannel* channel = new QWebChannel();
  page()->setWebChannel(channel);
  channel->registerObject(QString("qtMap"), this);

  this->load(QUrl("qrc:/data/map/index.html"));
}

MapRender::~MapRender() {
  /* QWebEnginePage does not take ownership of the QWebChannel */
  delete page()->webChannel();
}

void MapRender::countryClickedJs(QString country) {
  emit qobject_cast<Map*>(parentWidget())->countryClicked(country);
}

void MapRender::connectedJs() {
  emit resizeMapJs(width());
  emit highlightJs("Afghanistan");
}

void MapRender::resizeEvent(QResizeEvent*) {
  emit resizeMapJs(width());
}
