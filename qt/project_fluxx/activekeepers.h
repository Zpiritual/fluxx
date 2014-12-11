//This class contains small images of the active player's keepers and is shown above the active hand

#ifndef ACTIVEKEEPERS_H
#define ACTIVEKEEPERS_H

#include <QWidget>
#include <QtWidgets>
#include "cardbutton.h"
#include "CardContainer.h"
#include "cardidloop.h"
#include <vector>

class ActiveKeepers : public QWidget
{
    Q_OBJECT
public:
    explicit ActiveKeepers(QWidget *parent = 0);
    ~ActiveKeepers();

    void updateCards(const CardContainer&);
    void connectButtons(CardIdLoop& loop);

private:
    QHBoxLayout* layout;
    std::vector<CardButton*> buttons_;

    void uiElements();
};

#endif // ACTIVEKEEPERS_H
