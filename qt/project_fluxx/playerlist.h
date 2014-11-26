#ifndef PLAYERLIST_H
#define PLAYERLIST_H

#include <QWidget>
#include <QtWidgets>
#include "PlayerID.h"
#include "BoardSnapshot.h"
#include "playerlistitem.h"

class PlayerList : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerList(const std::vector<PlayerID>&, QWidget *parent = 0);
    ~PlayerList();
    const PlayerID pickPlayer() const;
    void updatePlayers(BoardSnapshot*);

private:
    QVBoxLayout* vertical_layout;
    std::vector<PlayerID> player_ids;
    std::vector<PlayerListItem*> players;


signals:

public slots:

};



#endif // PLAYERLIST_H
