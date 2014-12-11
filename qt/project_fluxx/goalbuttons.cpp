#include "goalbuttons.h"

GoalButtons::GoalButtons(QWidget *parent) :
    QWidget(parent)
{
    uiElements();
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
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);
}

void GoalButtons::updateCards(const CardContainer& container)
{
    this->setAutoFillBackground(false);

    buttons_.clear();
    if (layout->layout() != NULL) //Remove everything in the widget
    {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != NULL)
        {
            delete item->widget();
            delete item;
        }
    }

    cards_ = container.getCards();

    for(CardID card : cards_) //Add new cards
    {
        CardButton* tempbutton = new CardButton(card, this);
        tempbutton->smallButton();
        layout->addWidget(tempbutton);
        buttons_.push_back(tempbutton);
    }
}

void GoalButtons::setConnections(CardIdLoop &loop)
{
    BigCardCollection* bigcollection = new BigCardCollection{cards_, loop};
    bigcollection->show();
    loop.exec();
    bigcollection->close();
}
