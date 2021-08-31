#include "stonksland.h"

#include <QApplication>

#include "getinfo.h"
#include "stockmarket.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  StonksLand w;
  w.show();
  return a.exec();
}
