#include "cardbutton.h"


CardButton::CardButton(const CardID& id, QWidget *parent) :
    QPushButton(parent)
{
    uiElements(id);
}

CardButton::~CardButton()
{
    delete icon;
    delete id_;
}

void CardButton::smallButton()
{
    this->setMaximumSize(85,130);
    this->setMinimumSize(85,130);

    this->setIconSize(QSize(85,132));
}

const CardID& CardButton::getCardId() const
{
    return *id_;
}

void CardButton::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton && !icon->isNull())
    {
        BigCard* big_card_window = new BigCard(id_, this);

        big_card_window->show();
    }
    QPushButton::mouseReleaseEvent(e);
}

void CardButton::uiElements(const CardID& id)
{
    QString temp_string{"./Images/"+QString::number(id.val)+".png"};

    icon = new QIcon(temp_string);
    id_ = new CardID(id.val);

    this->setIcon(*icon);

    this->setMinimumSize(170,259);
    this->setMaximumSize(170,259);

    this->setIconSize(QSize(170,259));
}


