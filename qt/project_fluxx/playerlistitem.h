//Widget that show information about one player in the game.
//Has a button to show a players keepers and will show the size of a players hand
//and how many keepers a player have

#ifndef PLAYERLISTITEM_H
#define PLAYERLISTITEM_H

#include <QWidget>
#include <QtWidgets>
#include "profilename.h"
#include "bigcardcollection.h"

class PlayerListItem : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerListItem(const ProfileName&, QWidget *parent = 0);
    ~PlayerListItem();
    int getHandCount() const;
    int getKeeperCount() const;
    void updateCards(const std::vector<CardID>, const std::vector<CardID>);

    void setActivePlayer();
    void setNextPlayer();
    void setInactivePlayer();

    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

    const ProfileName getPlayerName() const;

private:
    std::vector<CardID> hand;
    std::vector<CardID> keepers_id;
    ProfileName player_name; //{"tempName"};

    QPushButton* keeper_button;

    QVBoxLayout* vertical_layout;

    QLabel* name_label;
    QLabel* card_count;
    QLabel* keeper_count;

    bool state;

    void uiElements();
    void connectSignals();

signals:
    void clicked();

public slots:
    void showKeepers();

};

#endif // PLAYERLISTITEM_H
