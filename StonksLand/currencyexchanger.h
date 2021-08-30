#ifndef CURRENCY_EXCHANGER_H
#define CURRENCY_EXCHANGER_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>



class CurrencyExchanger : public QWidget
{
    Q_OBJECT

public:
    CurrencyExchanger(QWidget *parent = nullptr);
    ~CurrencyExchanger();
    void compute(QString, QString);

protected slots:
    void convert(int);
    void convert(QString);

private:
    QLabel *valueUnit;
    QLineEdit *resultConv;
    QJsonValue *json_list;
    QComboBox *comboListA;
    QComboBox *comboListB;
    QLineEdit *valueConv;



};
#endif // CurrencyExchanger_H
