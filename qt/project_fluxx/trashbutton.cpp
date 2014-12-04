#include "trashbutton.h"

TrashButton::TrashButton(QWidget *parent) :
    QPushButton(parent)
{
    this->setMinimumSize(170,259);
    this->setMaximumSize(170,259);

    this->setIconSize(QSize(170,259));
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickbutton()));
}

TrashButton::~TrashButton()
{
}

void TrashButton::updateCards(const CardContainer cards)
{
    cards_ = cards.getCards();

    if(cards.getSize() != 0)
    {
        QString temp_string{":Images/"+QString::number(cards_.back().val)+".png"};
        icon = QIcon{temp_string};
        this->setIcon(icon);

    }
}

void TrashButton::clickbutton()
{
    if(cards_.size() != 0)
    {
        BigCardCollection* bigcollection = new BigCardCollection{cards_};
        bigcollection->show();
    }
}

void TrashButton::setConnections(CardIdLoop& loop)
{
    BigCardCollection* bigcollection = new BigCardCollection{cards_, loop};
    bigcollection->show();
    loop.exec();
    bigcollection->close();
    qDebug() << "setConnections in TrashButton";
}
