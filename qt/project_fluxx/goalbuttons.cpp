#include "goalbuttons.h"

GoalButtons::GoalButtons(QWidget *parent) :
    QWidget(parent)
{
    uiElements();
}

void GoalButtons::setConnections(CardIdLoop &loop)
{
    BigCardCollection* bigcollection = new BigCardCollection{cards_, loop};
    bigcollection->setWindowTitle(QString("Goals"));
    bigcollection->show();
    loop.exec();
    bigcollection->close();
}

void GoalButtons::updateCards(const CardContainer& container)
{
    buttons_.clear();

    this->setAutoFillBackground(false);

    if (layout->layout() != NULL)
    {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != NULL)
        {
            delete item->widget();
            delete item;
        }
    }

    cards_ = container.getCards();

    for(CardID card : cards_)
    {
        CardButton* tempbutton = new CardButton(card, this);
        tempbutton->smallButton();
        layout->addWidget(tempbutton);
        buttons_.push_back(tempbutton);
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
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);
}

