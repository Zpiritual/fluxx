#ifndef PLAYERLIST_H
#define PLAYERLIST_H

#include <QWidget>
#include <QtWidgets>
#include "profilename.h"
#include "BoardSnapshot.h"
#include "playerlistitem.h"
#include "enums.h"

class PlayerList : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerList(const std::vector<ProfileName>&, QWidget *parent = 0);
    ~PlayerList();
    const PlayerID pickPlayer() const;
    void updatePlayers(BoardSnapshot*);
    void updatePlayerState(int, int, const Direction&);

private:
    QVBoxLayout* vertical_layout;
    std::vector<ProfileName> player_ids;
    std::vector<PlayerListItem*> players;

    int current_player;
    int next_player;


signals:

public slots:

};



#endif // PLAYERLIST_H
