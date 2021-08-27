#pragma once

#include "maprender.h"

#include <QWidget>

class Map : public QWidget
{
  Q_OBJECT
public:
  Map(QWidget *parent = nullptr);

public slots:
  void highlight(QString country);
  void reset();

signals:
  void countryClicked(QString country);

protected:
  MapRender *mapRender;
};

