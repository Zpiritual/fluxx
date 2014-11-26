#include "goalbuttons.h"

GoalButtons::GoalButtons(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();

    this->setLayout(layout);

}

void GoalButtons::setConnections(QEventLoop &loop)
{
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));
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

