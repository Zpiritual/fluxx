#include "activehand.h"

ActiveHand::ActiveHand(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();
    this->setMaximumHeight(300);
    this->setLayout(layout);
}

void ActiveHand::update()
{

}
