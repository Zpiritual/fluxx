#include "activehand.h"

ActiveHand::ActiveHand(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();

//    for(int i = 1; i<=12; ++i)
//    {
//        CardButton* temp = new CardButton(CardID(i));
//        layout->addWidget(temp);

//    }
    this->setMaximumHeight(259);
    this->setMinimumHeight(259);
    this->setLayout(layout);
}

void ActiveHand::update()
{

}

void ActiveHand::connectButtons()
{

}
