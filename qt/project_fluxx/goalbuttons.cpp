#include "goalbuttons.h"

GoalButtons::GoalButtons(QWidget *parent) :
    QWidget(parent)
{
    uiElements();
}

void GoalButtons::setConnections(CardIdLoop &loop)
{
    BigCardCollection* bigcollection = new BigCardCollection{cards_, loop};
    bigcollection->show();
    loop.exec();
    bigcollection->close();
}

void GoalButtons::updateCards(const CardContainer& container)
{
    cards_ = container.getCards();
    //Fel i cards_ anatagligen container som är dealocated
    buttons_.clear();
    while(!(layout->isEmpty()))
    {
        QLayoutItem* temp = layout->itemAt(0);
        layout->removeItem(temp);
        delete temp;
    }

    for(auto card : cards_)
    {
        CardButton* tempbutton = new CardButton{card};
        buttons_.push_back(tempbutton);
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

void GoalButtons::uiElements()
{
    layout = new QVBoxLayout();

    this->setLayout(layout);
}

