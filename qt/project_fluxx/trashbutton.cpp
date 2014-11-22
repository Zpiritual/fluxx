#include "trashbutton.h"

TrashButton::TrashButton(QWidget *parent) :
    QPushButton(parent)
{
    QString temp_string{":Images/"+QString::number(6)+".png"};

    icon = new QIcon(temp_string);


    this->setIcon(*icon);


    this->setMinimumSize(170,259);
    this->setMaximumSize(170,259);

    this->setIconSize(QSize(170,259));
}

TrashButton::~TrashButton()
{
}
