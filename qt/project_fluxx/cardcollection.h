//This is a helper class to BigCardCollection

#ifndef CARDCOLLECTION_H
#define CARDCOLLECTION_H

#include <QWidget>
#include <QtWidgets>
#include "CardID.h"
#include "cardbutton.h"
#include "cardidloop.h"

class CardCollection : public QWidget
{
    Q_OBJECT
public:
    explicit CardCollection(const std::vector<CardID>& ,QWidget *parent = 0);
    explicit CardCollection(const std::vector<CardID>&, CardIdLoop& loop ,QWidget *parent = 0);

    ~CardCollection();

private:
    QHBoxLayout* horizontal_layout;
    std::vector<CardButton*> cards;

    void addCards(const std::vector<CardID>&);
};

#endif // CARDCOLLECTION_H
