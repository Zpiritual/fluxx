#include "deckbutton.h"
#include <QMouseEvent>
#include <QDebug>


DeckButton::DeckButton(QWidget *parent) :
    QPushButton(parent)
{

    QString temp_string{":Images/"+QString::number(0)+".png"};

    icon = new QIcon(temp_string);


    this->setIcon(*icon);

    this->setMinimumSize(170,259);
    this->setMaximumSize(170,259);

    this->setIconSize(QSize(170,259));
}

void DeckButton::updateCards(const CardContainer& cards)
{
    cards_ = cards.getCards();
}

DeckButton::~DeckButton()
{
}

void DeckButton::mouseReleaseEvent(QMouseEvent *e) {
if (e->button() == Qt::RightButton)
{
    qDebug() << "Add right click on button functionality";
}
QPushButton::mouseReleaseEvent(e);
}
