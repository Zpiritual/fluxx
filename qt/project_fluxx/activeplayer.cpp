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
    scroll_area_keepers->setMaximumHeight(265);
    scroll_area_keepers->setMinimumHeight(265);
    scroll_area_hand->setMinimumHeight(265);
    scroll_area_hand->setMaximumHeight(265);


    layout->setAlignment(scroll_area_hand, Qt::AlignBottom);
    layout->setAlignment(scroll_area_keepers, Qt::AlignTop);



    this->setLayout(layout);
}

ActivePlayer::~ActivePlayer(){
}
