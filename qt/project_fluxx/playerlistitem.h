#ifndef PLAYERLISTITEM_H
#define PLAYERLISTITEM_H

#include <QWidget>
#include <QtWidgets>
#include <cardbutton.h>
#include "PlayerID.h"

class PlayerListItem : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerListItem(const PlayerID&, QWidget *parent = 0);
    int getHandCount() const;
    void updateCards(const std::vector<CardID*>&, const std::vector<CardID*>&);

private:
    std::vector<CardID*> hand;
    std::vector<CardID*> keepers_id;
    PlayerID player_name;

    QVBoxLayout* vertical_layout;

    QLabel name_label;
    QLabel card_count;
    std::vector<CardButton*> keepers;

signals:

public slots:

};

#endif // PLAYERLISTITEM_H
