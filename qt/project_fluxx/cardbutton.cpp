#include "cardbutton.h"


CardButton::CardButton(CardID id, QWidget *parent) :
    QPushButton(parent)
{
    QString temp_string{":Images/"+QString::number(id.val)+".png"};

    icon = new QIcon(temp_string);
    id_ = new CardID(id.val);

    this->setIcon(*icon);

    this->setMinimumSize(170,259);
    this->setMaximumSize(170,259);

    this->setIconSize(QSize(170,259));
}

CardButton::CardButton(CardID* id, Gui*, QWidget *parent) :
    QPushButton(parent)
{
    QString temp_string{":Images/"+QString::number(id->val)+".png"};

    icon = new QIcon(temp_string);
    id_ = new CardID(id->val);

    this->setIcon(*icon);

    this->setMinimumSize(170,259);
    this->setMaximumSize(170,259);

    this->setIconSize(QSize(170,259));
}

CardButton::~CardButton()
{
}

const CardID& CardButton::getCardId() const
{
    return *id_;
}

void CardButton::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton)
    {
     BigCard* big_card_window = new BigCard(id_,this);

     big_card_window->move(QApplication::desktop()->screen()->rect().center() - big_card_window->rect().center());

        qDebug() << "Add right click on button functionality";
    }
    QPushButton::mouseReleaseEvent(e);
}

void CardButton::buttonpressed()
{
    //parent()->
}

void CardButton::smallButton()
{
    this->setMaximumSize(85,135);
    this->setMinimumSize(85,135);

    this->setIconSize(QSize(85,135));
}
