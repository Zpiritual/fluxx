//THIS FILE IS NO LONGER IN USE AND IS RETIRED

#include "activeplayer.h"

ActivePlayer::ActivePlayer(QWidget *parent) :
    QWidget(parent)
{
    uiElements();
}

void ActivePlayer::updateCards(const BoardSnapshot* const snapshot, const bool changed_player)
{
    active_hand->hide();  //Removes background colors getting stuck when hand shrinks
    active_hand->show();
    if(!changed_player)
    {
        if(snapshot->getContainer(CardContainerID("tempA")).getSize() != 0)
        {
            active_hand->updateCards(snapshot->getContainer(CardContainerID("tempA")));
        }
        else
        {
            active_hand->updateCards(snapshot->getContainer(CardContainerID(snapshot->current_player.getString()+"_hand")));
        }
        active_keepers->updateCards(snapshot->getContainer(CardContainerID(snapshot->current_player.getString()+"_keepers")));
    }
    else
    {

        active_hand->updateCards(snapshot->getContainer(snapshot->active_player.getString()+"_hand"));
        active_keepers->updateCards(snapshot->getContainer(snapshot->active_player.getString()+"_keepers"));
    }
}

ActivePlayer::~ActivePlayer()
{
    delete active_hand;
    delete active_keepers;
    delete scroll_area_hand;
    delete scroll_area_keepers;
    delete layout;
}

void ActivePlayer::connectActiveKeepers(CardIdLoop& loop)
{
    active_keepers->connectButtons(loop);
}

void ActivePlayer::connectActiveHand(CardIdLoop& loop)
{
    active_hand->connectButtons(loop);
}

void ActivePlayer::endTurn(const ProfileName& next_player, QEventLoop& loop)
{
    scroll_area_hand->hide();
    SwitchPlayer* switch_player = new SwitchPlayer(next_player, loop, true);
    layout->addWidget(switch_player);
    loop.exec();

    layout->removeWidget(switch_player);
    delete switch_player;
    scroll_area_hand->show();
}

void ActivePlayer::changePlayer(const ProfileName& next_player, QEventLoop& loop)
{
    scroll_area_hand->hide();
    SwitchPlayer* change_player = new SwitchPlayer(next_player, loop, false);
    layout->addWidget(change_player);
    loop.exec();

    layout->removeWidget(change_player);
    delete change_player;
    scroll_area_hand->show();
}

void ActivePlayer::uiElements()
{
    layout = new QVBoxLayout();
    scroll_area_hand = new QScrollArea();
    scroll_area_keepers = new QScrollArea();


    active_hand = new ActiveHand(this);
    active_keepers = new ActiveKeepers(this);
    layout->addWidget(scroll_area_keepers);
    layout->addWidget(scroll_area_hand);

    scroll_area_keepers->setWidget(active_keepers);
    scroll_area_hand->setWidget(active_hand);
    scroll_area_keepers->setFrameShape(QFrame::NoFrame);
    scroll_area_hand->setFrameShape(QFrame::NoFrame);


    scroll_area_hand->setMinimumHeight(active_hand->minimumSizeHint().height() + scroll_area_hand->horizontalScrollBar()->height() + 10);
    scroll_area_hand->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout->setSpacing(0);
    this->setLayout(layout);
}
