#include "goalbuttons.h"

GoalButtons::GoalButtons(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();

    this->setLayout(layout);

}

void GoalButtons::setConnections(CardIdLoop &loop)
{
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));
}

void GoalButtons::updateCards(const CardContainer& container)
{
    std::vector<CardID> cards_ = container.getCards();
    //Fel i cards_ anatagligen container som är dealocated
    while(!(layout->isEmpty()))
    {
        QLayoutItem* temp = layout->itemAt(0);
        layout->removeItem(temp);
    }

    for(auto card : cards_)
    {
        CardButton* tempbutton = new CardButton{card};
        tempbutton->smallButton();
        layout->addWidget(tempbutton);
    }

}

GoalButtons::~GoalButtons()
{
    for(CardButton* button : buttons_)
        delete button;
    delete layout;
}

