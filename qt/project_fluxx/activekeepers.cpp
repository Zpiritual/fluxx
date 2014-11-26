#include "activekeepers.h"

ActiveKeepers::ActiveKeepers(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();

    this->setMaximumHeight(135);
    this->setMinimumHeight(135);

    this->setLayout(layout);
}

void ActiveKeepers::update(const CardContainer& container)
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

void ActiveKeepers::connectButtons(QEventLoop &loop)
{
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));

}
