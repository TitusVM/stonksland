#ifndef LIST_H
#define LIST_H

#include <QListWidget>
#include <fstream>
#include <vector>

#include "currency.h"

class List : public QListWidget
{
    Q_OBJECT

public:
    List(std::vector<Currency> currencies);
    ~List();
};
#endif // LIST_H
