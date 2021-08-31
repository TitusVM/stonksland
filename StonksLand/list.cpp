#include "list.h"
#include "infosmonnaie.h"
#include <QtWidgets>

List::List(std::vector<Currency> currencies)
    : QListWidget()
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

    /* Add to list */
    for(std::size_t i = 1; i < currencies.size(); i++)
    {
        QListWidgetItem *listItem = new QListWidgetItem;
        listItem->setText(currencies[i].getName());
        listItem->setFont(font);
        addItem(listItem);
    }

    setMinimumWidth(410);
}

List::~List()
{
}

