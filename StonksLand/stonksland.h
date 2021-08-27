#pragma once

#include <QWidget>

#include "getinfo.h"

class StonksLand : public QWidget
{
  Q_OBJECT

public:
  StonksLand(QWidget *parent = nullptr);
  ~StonksLand();

protected:
  GetInfo *infos;
};
