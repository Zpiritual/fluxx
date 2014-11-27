#include "activehand.h"

ActiveHand::ActiveHand(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();

    this->setMaximumHeight(259);
    this->setMinimumHeight(259);
    this->setLayout(layout);
}

void ActiveHand::update(const CardContainer& container)
{
    std::vector<CardID> cards = container.getCards();

    while(!(layout->isEmpty()))
    {
        QLayoutItem* temp = layout->itemAt(0);
        layout->removeItem(temp);
    }
    for(auto card : cards)
    {
        CardButton* tempbutton = new CardButton(card);
        layout->addWidget(tempbutton);
        buttons_.push_back(tempbutton);
    }
}

void ActiveHand::connectButtons(CardIdLoop& loop)
{
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));

}
