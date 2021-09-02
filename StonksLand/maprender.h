#pragma once

#include <QWebEngineView>

class MapRender : public QWebEngineView
{
  Q_OBJECT

public:
  MapRender(QWidget *parent);
  ~MapRender();

public slots:
  void countryClickedJs(QString country);
  void connectedJs();

signals:
  void resetJs();
  void highlightJs(QString country);
  void resizeMapJs(int width);

protected:
  void resizeEvent(QResizeEvent *event) override;
};

