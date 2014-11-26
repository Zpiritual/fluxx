#include "goalbuttons.h"

GoalButtons::GoalButtons(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();

    this->setLayout(layout);

}

void GoalButtons::connectButtons(QEventLoop &loop)
{

}

void GoalButtons::update(const CardContainer& container)
{
    std::vector<CardID> cards_ = container.getCards();

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

