#include "playerlist.h"

PlayerList::PlayerList(const std::vector<PlayerID>& plyers, QWidget *parent) :
    QWidget(parent)
{
    vertical_layout = new QVBoxLayout();
    player_ids = plyers;

    for(int i = 0; i < player_ids.size(); i++)
    {
        players.push_back(new PlayerListItem(player_ids.at(i)));
        vertical_layout->addWidget(players.at(i));
    }

    this->setLayout(vertical_layout);
    this->show();
}

PlayerList::~PlayerList(){
}

const PlayerID PlayerList::pickPlayer() const
{

}

void PlayerList::updatePlayers(BoardSnapshot* board)
{
    for(int i = 0; i < player_ids.size(); i++)
    {
        const CardContainerID player_hand{std::string{"Player" + std::to_string(i+1) + "_hand"}};
        const CardContainerID player_keepers{std::string{"Player" + std::to_string(i+1) + "_keepers"}};
        CardContainer hand{board->getContainer(player_hand)};
        CardContainer keepers{board->getContainer(player_hand)};
        players.at(i)->updateCards(hand.getCards(), keepers.getCards());
    }
}
