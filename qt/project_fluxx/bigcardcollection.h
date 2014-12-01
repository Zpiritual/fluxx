#ifndef BIGCARDCOLLECTION_H
#define BIGCARDCOLLECTION_H

#include <QWidget>
#include <QtWidgets>
#include "CardID.h"
#include "cardcollection.h"
#include "cardbutton.h"
#include "cardidloop.h"


class BigCardCollection : public QWidget
{
    Q_OBJECT
public:
    explicit BigCardCollection(const std::vector<CardID>&, QWidget *parent = 0);
    ~BigCardCollection();
    explicit BigCardCollection(const std::vector<CardID>&, CardIdLoop&, QWidget *parent = 0);

private:
    QScrollArea* scroll_area;
    QHBoxLayout* horizontal_layout;
    CardCollection* card_collection;

    void setConnections(CardIdLoop&);

signals:

public slots:

};



#endif // BIGCARDCOLLECTION_H
