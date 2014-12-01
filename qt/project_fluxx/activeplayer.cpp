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

    this->setMinimumHeight(300);

    layout->setAlignment(scroll_area_keepers, Qt::AlignTop);
    layout->setAlignment(scroll_area_hand, Qt::AlignTop);
    scroll_area_keepers->setFrameShape(QFrame::NoFrame);
    scroll_area_hand->setFrameShape(QFrame::NoFrame);

    this->setLayout(layout);
}

void ActivePlayer::updateCards(const BoardSnapshot* const snapshot)
{

    if(snapshot->getContainer(CardContainerID("tempB")).getSize() != 0)
    {
        active_hand->updateCards(snapshot->getContainer(CardContainerID("TempB")));
    }
    else if(snapshot->getContainer(CardContainerID("tempA")).getSize() != 0)
    {
        active_hand->updateCards(snapshot->getContainer(CardContainerID("tempA")));
    }
    else
    {
        active_hand->updateCards(snapshot->getContainer(CardContainerID(snapshot->current_player.getString()+"_hand")));
    }
    active_keepers->updateCards(snapshot->getContainer(CardContainerID(snapshot->current_player.getString()+"_keepers")));
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

void ActivePlayer::switchPlayer(const ProfileName& next_player)
{
    scroll_area_hand->hide();
    QEventLoop loop;
    SwitchPlayer* switch_player = new SwitchPlayer(next_player, loop);
    layout->addWidget(switch_player);
    loop.exec();

    layout->removeWidget(switch_player);
    delete switch_player;
    scroll_area_hand->show();
}
