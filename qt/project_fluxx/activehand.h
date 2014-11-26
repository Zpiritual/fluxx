#ifndef ACTIVEHAND_H
#define ACTIVEHAND_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "cardbutton.h"

class ActiveHand : public QWidget
{
    Q_OBJECT
public:
    explicit ActiveHand(QWidget *parent = 0);
    void update(); //Gå till qlistwidget och hämta hand mha gethand(playerID),
    //eventuellt görs detta i activeplayer
private:
    std::vector<CardButton> cards;
    QHBoxLayout* layout;
signals:

public slots:

};

#endif // ACTIVEHAND_H
