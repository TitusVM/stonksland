#pragma once

#include <QChartView>
#include <QLineSeries>

using namespace QtCharts;

class Graph : public QChartView
{
  Q_OBJECT

public:
  Graph();
  ~Graph();

  void display(QString currencyIndex, QLineSeries* rates, QString dateFormat, bool isMainWindow);
};

