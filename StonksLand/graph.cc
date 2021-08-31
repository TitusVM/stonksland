#include "graph.h"

#include <QAreaSeries>
#include <QDateTimeAxis>

Graph::Graph()
{
}

void Graph::display(QString currencyIndex, QLineSeries* rates, QString dateFormat, bool isMainWindow) {
  double highest = INT_MIN;
  double lower = INT_MAX;
  for (int i = 0; i < rates->count(); ++i) {
    double rate = rates->at(i).y();
    if (rate > highest) {
      highest = rate;
    }

    if (rate < lower) {
      lower = rate;
    }
  }

  QPen pen(0x059605);
  pen.setWidth(3);
  rates->setPen(pen);

  QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
  gradient.setColorAt(0.0, 0x3cc63c);
  gradient.setColorAt(1.0, 0x26f626);
  gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
  rates->setBrush(gradient);

  QChart *chart = new QChart;
  chart->legend()->setVisible(false);
  chart->setContentsMargins(0, 0, 0, 0);
  chart->addSeries(rates);
  if(isMainWindow)
  {
      chart->setTitle("Price of Euro in " + currencyIndex);
  }
  else
  {
      chart->setTitle(currencyIndex);
  }

  chart->createDefaultAxes();

  chart->removeAxis(chart->axes(Qt::Horizontal).first());

  QDateTimeAxis *x = new QDateTimeAxis;
  //x->setTickCount(10);
  x->setFormat(dateFormat);
  chart->addAxis(x, Qt::AlignBottom);
  rates->attachAxis(x);

  chart->axes(Qt::Vertical).first()->setRange(lower, highest + 1);

  setChart(chart);
  setRenderHint(QPainter::Antialiasing);
  this->setMinimumHeight(200);
}

Graph::~Graph() {}
