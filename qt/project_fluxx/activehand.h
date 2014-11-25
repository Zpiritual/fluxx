#ifndef ACTIVEHAND_H
#define ACTIVEHAND_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "cardbutton.h"
class Gui;

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
    Gui* guiptr_;
signals:

public slots:

};

#include "gui.h"
#endif // ACTIVEHAND_H
