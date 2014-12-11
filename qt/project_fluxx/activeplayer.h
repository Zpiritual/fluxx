//THIS FILE IS NO LONGER IN USE AND IS RETIRED

#ifndef ACTIVEPLAYER_H
#define ACTIVEPLAYER_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "PlayerID.h"
#include "activehand.h"
#include "activekeepers.h"
#include "BoardSnapshot.h"
#include "CardContainerID.h"
#include "cardidloop.h"
#include "BoardSnapshot.h"
#include "switchplayer.h"
#include "profilename.h"

class ActivePlayer : public QWidget
{
    Q_OBJECT
public:
    explicit ActivePlayer(QWidget *parent = 0);
    ~ActivePlayer();

    void updateCards(const BoardSnapshot* const, const bool);
    void connectActiveKeepers(CardIdLoop&);
    void connectActiveHand(CardIdLoop&);
    void endTurn(const ProfileName&, QEventLoop&);
    void changePlayer(const ProfileName&, QEventLoop&);

private:
    QVBoxLayout* layout;
    QScrollArea* scroll_area_hand;
    QScrollArea* scroll_area_keepers;
    ActiveHand* active_hand;
    ActiveKeepers* active_keepers;

    void uiElements();
};



#endif // ACTIVEPLAYER_H
