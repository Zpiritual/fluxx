#ifndef CARDCOLLECTION_H
#define CARDCOLLECTION_H

#include <QWidget>
#include <QtWidgets>
#include "CardID.h"
#include "cardbutton.h"

class CardCollection : public QWidget
{
    Q_OBJECT
public:
    explicit CardCollection(const std::vector<CardID>& ,QWidget *parent = 0);
    ~CardCollection();
private:
    QHBoxLayout* horizontal_layout;

    std::vector<CardButton*> cards;
signals:

public slots:

};

#endif // CARDCOLLECTION_H
