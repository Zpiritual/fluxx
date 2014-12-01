#include "cardidloop.h"

CardIdLoop::CardIdLoop(QObject *parent) :
    QObject(parent)
{
    loop_;
}

void CardIdLoop::quit()
{
    card_button_id = dynamic_cast<CardButton*>(sender())->getCardId().val;
    loop_.quit();
}

const CardID CardIdLoop::getCardId()
{
    return card_button_id;
}

void CardIdLoop::exec()
{
    loop_.exec();
}
