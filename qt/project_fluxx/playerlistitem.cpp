#include "playerlistitem.h"

PlayerListItem::PlayerListItem(const PlayerID& name, QWidget *parent) :
    player_name(name), QWidget(parent)
{
    vertical_layout = new QVBoxLayout;
    name_label.setText(QString::fromStdString(player_name.val));
    card_count.setText(QString::number(hand.size()));

    keepers_id.push_back(new CardID{1});
    keepers_id.push_back(new CardID{2});
    keepers_id.push_back(new CardID{3});

    for(int i=0; i < keepers_id.size(); ++i)
    {
        keepers.push_back(new CardButton(keepers_id.at(i)));
    }
}

int PlayerListItem::getHandCount() const
{
    return hand.size();
}

void PlayerListItem::updateCards(const std::vector<CardID*>& hnd, const std::vector<CardID*>& keeprs)
{
    hand = hnd;
    keepers_id = keeprs;
}
