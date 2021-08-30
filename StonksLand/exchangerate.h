#ifndef GRAPH_WIDGET_H
#define GRAPH_WIDGET_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QLabel>
#include <QLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class exchangeRate; }
QT_END_NAMESPACE

class ExchangeRate : public QWidget
{
    Q_OBJECT

public:
    void updateRate(QString);
    ExchangeRate(QWidget *parent = nullptr);
    ~ExchangeRate();

private:
    QJsonValue *json_list;
    QGridLayout *layout;
    QLabel *exchangeRate;
    QLabel *title;

};

#endif // GRAPH_WIDGET_H
