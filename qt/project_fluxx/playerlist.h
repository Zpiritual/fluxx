#ifndef PLAYERLIST_H
#define PLAYERLIST_H

#include <QWidget>
#include "../../include/PlayerID.h"

class PlayerList : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerList(QWidget *parent = 0);
    ~PlayerList();
    const PlayerID pickPlayer() const;

signals:

public slots:

};

#endif // PLAYERLIST_H
