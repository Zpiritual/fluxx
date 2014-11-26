#ifndef PLAYERLISTITEM_H
#define PLAYERLISTITEM_H

#include <QWidget>
#include <QtWidgets>
#include "PlayerID.h"
#include "bigcardcollection.h"

class PlayerListItem : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerListItem(const PlayerID&, QWidget *parent = 0);
    ~PlayerListItem();
    int getHandCount() const;
    int getKeeperCount() const;
    void updateCards(const std::vector<CardID>&, const std::vector<CardID>&);

private:
    std::vector<CardID> hand;
    std::vector<CardID> keepers_id;
    PlayerID player_name;

    QPushButton* keeper_button;

    QVBoxLayout* vertical_layout;

    QLabel* name_label;
    QLabel* card_count;
    QLabel* keeper_count;

    BigCardCollection* big_keepers;

signals:

public slots:
    void showKeepers();

};

#endif // PLAYERLISTITEM_H
