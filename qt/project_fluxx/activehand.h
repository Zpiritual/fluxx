//This class contains the active player's handthat is shown at the bottom of the window in the middle

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
    ~ActiveHand();

    void updateCards(const CardContainer);
    void connectButtons(CardIdLoop& loop);

private:
    QHBoxLayout* layout;
    std::vector<CardButton*> buttons_;

    void uiElements();
};

#endif // ACTIVEHAND_H
