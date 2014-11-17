#include "card.h"

Card::Card(int id, QWidget *parent) :
    QPushButton(parent)
{
    card_id = id;
    QString temp_string{":Images/"+QString::number(card_id)+".png"};

    this->setIcon(QIcon(temp_string));

}

Card::~Card(){
}
