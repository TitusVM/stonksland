#ifndef LIST_H
#define LIST_H

#include <QListWidget>
#include <fstream>
#include <vector>

class List : public QListWidget
{
    Q_OBJECT

public:
    List(QWidget *parent = nullptr);
    ~List();

private:
    std::vector<std::vector<std::string>> *vecFile;
};
#endif // LIST_H
