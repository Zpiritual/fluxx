#include "activeplayer.h"

ActivePlayer::ActivePlayer(QWidget *parent) :
    QWidget(parent)
{
    layout = new QVBoxLayout();
    scroll_area_hand = new QScrollArea();
    scroll_area_keepers = new QScrollArea();

    active_hand = new ActiveHand();
    active_keepers = new ActiveKeepers();
    layout->addWidget(scroll_area_keepers);
    layout->addWidget(scroll_area_hand);

    scroll_area_keepers->setWidget(active_keepers);
    scroll_area_hand->setWidget(active_hand);
    scroll_area_keepers->setMaximumHeight(140);
    scroll_area_keepers->setMinimumHeight(140);
    scroll_area_hand->setMinimumHeight(265);
    scroll_area_hand->setMaximumHeight(265);

    this->setMinimumHeight(400);
    layout->setAlignment(scroll_area_hand, Qt::AlignBottom);
    layout->setAlignment(scroll_area_keepers, Qt::AlignTop);
    scroll_area_keepers->setFrameShape(QFrame::NoFrame);

    this->setLayout(layout);
}

void ActivePlayer::update(BoardSnapshot* snapshot)
{

    if(snapshot->getContainer(CardContainerID("tempB")).getSize() != 0)
    {
        active_hand->update(snapshot->getContainer(CardContainerID("TempB")));
    }
    else if(snapshot->getContainer(CardContainerID("tempA")).getSize() != 0)
    {
        active_hand->update(snapshot->getContainer(CardContainerID("tempA")));
    }
    else
    {
        active_hand->update(snapshot->getContainer(CardContainerID(snapshot->current_player.getString()+"_hand")));
        active_keepers->update(snapshot->getContainer(CardContainerID(snapshot->current_player.getString()+"_keepers")));
    }
}

ActivePlayer::~ActivePlayer()
{
    delete layout;
    delete scroll_area_hand;
    delete scroll_area_keepers;
    delete active_player;
    delete active_hand;
    delete active_keepers;
}

void ActivePlayer::connectActiveKeepers(CardIdLoop& loop)
{
    active_keepers->connectButtons(loop);
}

void ActivePlayer::connectActiveHand(CardIdLoop& loop)
{
    active_hand->connectButtons(loop);
}
