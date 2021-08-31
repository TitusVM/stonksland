#ifndef GRAPH_WIDGET_H
#define GRAPH_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QMap>

class ExchangeRate : public QWidget
{
    Q_OBJECT

public:
    void updateRate(QString);
    ExchangeRate(QMap<QString, double> const& rates);
    ~ExchangeRate();

private:
    QGridLayout *layout;
    QLabel *exchangeRate;
    QLabel *title;
    QMap<QString, double> rates;
};

#endif // GRAPH_WIDGET_H
