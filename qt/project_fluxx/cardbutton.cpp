#include "cardbutton.h"
#include "../../include/CardID.h"
#include <QMouseEvent>
#include <QDebug>

CardButton::CardButton(CardID id, QWidget *parent) :
    QPushButton(parent)
{
    QString temp_string{":Images/"+QString::number(id.val)+".png"};

    icon = new QIcon(temp_string);


    this->setIcon(*icon);

    this->setMinimumSize(170,259);
    this->setMaximumSize(170,259);

    this->setIconSize(QSize(170,259));


}

CardButton::~CardButton()
{
}

void CardButton::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton)
    {
        qDebug() << "Add right click on button functionality";
    }
    QPushButton::mouseReleaseEvent(e);
}
