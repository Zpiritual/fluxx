//Widget that contain one playerlistitem for each player in the game

#ifndef PLAYERLIST_H
#define PLAYERLIST_H

#include <QWidget>
#include <QtWidgets>
#include "profilename.h"
#include "BoardSnapshot.h"
#include "playerlistitem.h"
#include "enums.h"
#include "playerloop.h"

class PlayerList : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerList(const std::vector<ProfileName>&, QWidget *parent = 0);
    ~PlayerList();
    void updatePlayers(const BoardSnapshot* const);
    void updatePlayerState(int, int);

    void setConnections(const PlayerLoop&);
    PlayerID getPlayerId(const ProfileName) const;

private:
    QVBoxLayout* vertical_layout;
    std::vector<ProfileName> player_ids;
    std::vector<PlayerListItem*> players;

    void uiElements();
};



#endif // PLAYERLIST_H
