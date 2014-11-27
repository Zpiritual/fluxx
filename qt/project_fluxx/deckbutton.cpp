#include "deckbutton.h"
#include <QMouseEvent>
#include <QDebug>


DeckButton::DeckButton(QWidget *parent) :
    QPushButton(parent)
{

    QString temp_string{":Images/"+QString::number(0)+".png"};

    icon = new QIcon(temp_string);


    this->setIcon(*icon);

    this->setMinimumSize(85,130);
    this->setMaximumSize(85,130);

    this->setIconSize(QSize(85,130));
}

DeckButton::~DeckButton()
{
}
