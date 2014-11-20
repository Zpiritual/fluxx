#include "deckbutton.h"

DeckButton::DeckButton(QWidget *parent) :
    QPushButton(parent)
{

    QString temp_string{":Images/"+QString::number(5)+".png"};

    icon = new QIcon(temp_string);


    this->setIcon(*icon);

    this->setMinimumSize(156,259);
    this->setMaximumSize(156,259);

    this->setIconSize(QSize(156,259));
}

DeckButton::~DeckButton()
{
}
