#include "graph.h"

#include <QAreaSeries>
#include <QDateTimeAxis>

Graph::Graph()
{
}

void Graph::display(QString currency, QLineSeries* rates) {  
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

  lower -= 0.3;
  highest += 0.3;
  if (lower < 0) {
    lower = 0;
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
  chart->setDropShadowEnabled(true);
  chart->legend()->setVisible(false);
  chart->setContentsMargins(0, 0, 0, 0);
  chart->addSeries(rates);
  chart->setTitle("Price of " + currency + " in USD");
  chart->createDefaultAxes();

  chart->removeAxis(chart->axes(Qt::Horizontal).first());

  QDateTimeAxis *x = new QDateTimeAxis;
  x->setTickCount(10);
  x->setFormat("yyyy");
  chart->addAxis(x, Qt::AlignBottom);
  rates->attachAxis(x);

  chart->axes(Qt::Vertical).first()->setRange(lower, highest);

  setChart(chart);
  setRenderHint(QPainter::Antialiasing);
  this->setMinimumHeight(200);
  this->setMinimumWidth(400);

  QPointF p = chart->mapToValue(QPointF(100, 200));
  chart->setTitle(QString("") + p.x() + "a   " + p.y());
}

Graph::~Graph() {}
