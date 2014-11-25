#include "goalbuttons.h"

GoalButtons::GoalButtons(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();

    this->setLayout(layout);

}

void GoalButtons::updateCards(const CardContainer& cards)
{
    cards_ = cards.getCards();

    while(!(layout->isEmpty()))
    {
        QLayoutItem* temp = layout->itemAt(0);
        layout->removeItem(temp);
    }
    for(auto card : cards_)
    {
        layout->addWidget(new CardButton(card));
    }
}

GoalButtons::~GoalButtons()
{
}

