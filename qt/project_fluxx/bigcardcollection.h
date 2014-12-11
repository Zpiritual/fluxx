//This class is a used for showing several cards in a separate window than GUI

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
    //Used to show cards in a container
    explicit BigCardCollection(const std::vector<CardID>&, QWidget *parent = 0);
    //Used to select cards from a container
    explicit BigCardCollection(const std::vector<CardID>&, CardIdLoop&, QWidget *parent = 0);

    ~BigCardCollection();
    void closeEvent(QCloseEvent*);

private:
    QScrollArea* scroll_area;
    QHBoxLayout* horizontal_layout;
    CardCollection* card_collection;

    void setConnections(CardIdLoop&);

    void uiElements(const std::vector<CardID>&);
    void uiElements(const std::vector<CardID>&, CardIdLoop&);
};



#endif // BIGCARDCOLLECTION_H
