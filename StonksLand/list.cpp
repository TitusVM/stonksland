#include "list.h"
#include "csv.h"
#include "infosmonnaie.h"
#include <QtWidgets>

List::List(QWidget *parent)
    : QListWidget(parent)
{
    // QListWidget *countryList = new QListWidget(this);
    this->setSortingEnabled(true);
    this->setSpacing(8);
    this->setStyleSheet({"QListWidget { "
                                    "background: rgb(2,0,36);"
                                    "outline:none; } "

                                "QListWidget::item { "
                                    "border: 0px;"
                                    "border-radius: 15px; "
                                    "background: #99ceff; "
                                    "padding: 20px; "
                                    "height: 15; "
                                    "color: white; } "

                                "QListWidget::item:selected { "
                                    "border: 0px;"
                                    "color: #009900; "
                                    "background: #ccffcc; }"
                                "QListWidget::item:focus { "
                                    "outline: none;"
                                    "}"

                               });
    QFont font("Monospace");
    font.setPointSize(10);


    /* Declare file to use */
    std::ifstream ifsFile ("csv_combined.csv", std::ifstream::in);

    /* Read file contents */
    vecFile = new std::vector<std::vector<std::string>>;
    *vecFile = readCSV(ifsFile);

    /* Add to list */
    for(int i = 1; i < vecFile->size(); i++)
    {
        QListWidgetItem *listItem = new QListWidgetItem;
        std::string strItem((*vecFile)[i][1].begin(), (*vecFile)[i][1].end());
        QString qstrItem = QString::fromUtf8(strItem.c_str());

        /*QLabel *labelItem = new QLabel;
        labelItem->setText(qstrItem);*/

        listItem->setText(qstrItem);
        listItem->setFont(font);


        if(this->findItems(qstrItem, Qt::MatchExactly).isEmpty())
        {
            this->addItem(listItem);
        }
    }

    setMinimumWidth(410);
}

List::~List()
{
    delete vecFile;
}

