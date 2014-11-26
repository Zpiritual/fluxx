#ifndef BIGCARDCOLLECTION_H
#define BIGCARDCOLLECTION_H

#include <QWidget>
#include <QtWidgets>
#include "CardID.h"
#include "cardcollection.h"
#include "cardbutton.h"


class BigCardCollection : public QWidget
{
    Q_OBJECT
public:
    explicit BigCardCollection(const std::vector<CardID>&, QWidget *parent = 0);
    ~BigCardCollection();

private:
    QScrollArea* scroll_area;
    QHBoxLayout* horizontal_layout;
    CardCollection* card_collection;

signals:

public slots:

};



#endif // BIGCARDCOLLECTION_H
