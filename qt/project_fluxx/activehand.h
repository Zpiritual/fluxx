#ifndef ACTIVEHAND_H
#define ACTIVEHAND_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "cardbutton.h"
#include "cardidloop.h"
#include "CardContainer.h"

class ActiveHand : public QWidget
{
    Q_OBJECT
public:
    explicit ActiveHand(QWidget *parent = 0);
    void update(const CardContainer&); //Gå till qlistwidget och hämta hand mha gethand(playerID),
    //eventuellt görs detta i activeplayer
    void connectButtons(CardIdLoop &loop);
private:
    std::vector<CardButton*> buttons_;
    QHBoxLayout* layout;
signals:

public slots:

};

#endif // ACTIVEHAND_H
