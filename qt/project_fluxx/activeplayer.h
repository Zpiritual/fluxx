#ifndef ACTIVEPLAYER_H
#define ACTIVEPLAYER_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "PlayerID.h"
#include "activehand.h"
#include "activekeepers.h"
#include "BoardSnapshot.h"

class ActivePlayer : public QWidget
{
    Q_OBJECT
public:
    explicit ActivePlayer(QWidget *parent = 0);
    void update(BoardSnapshot*);
    ~ActivePlayer();
    void connectActiveKeepers();
    void connectActiveHand();

private:
    QVBoxLayout* layout;
    QScrollArea* scroll_area_hand;
    QScrollArea* scroll_area_keepers;
    PlayerID* active_player;
    ActiveHand* active_hand;
    ActiveKeepers* active_keepers;

signals:

public slots:

};



#endif // ACTIVEPLAYER_H
