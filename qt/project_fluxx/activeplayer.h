#ifndef ACTIVEPLAYER_H
#define ACTIVEPLAYER_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "PlayerID.h"
#include "gui.h"

class ActiveHand;
class ActiveKeepers;
class ActivePlayer : public QWidget
{
    Q_OBJECT
public:
    explicit ActivePlayer(QWidget *parent = 0);
    void update();
    ~ActivePlayer();

private:
    QVBoxLayout* layout;
    QScrollArea* scroll_area_hand;
    QScrollArea* scroll_area_keepers;
    PlayerID* active_player;
    ActiveHand* active_hand;
    ActiveKeepers* active_keepers;
    Gui* parent2;

signals:

public slots:

};


#include "activehand.h"
#include "activekeepers.h"
#endif // ACTIVEPLAYER_H
