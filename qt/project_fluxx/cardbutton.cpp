#include "cardbutton.h"
#include "../../include/CardID.h"

CardButton::CardButton(CardID id, QWidget *parent) :
    QPushButton(parent)
{

    QString temp_string{":Images/"+QString::number(id.val)+".png"};

    this->setIcon(QIcon(temp_string));
}

CardButton::~CardButton()
{
}
