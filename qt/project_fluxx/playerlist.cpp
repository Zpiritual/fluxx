#include "playerlist.h"

PlayerList::PlayerList(const std::vector<PlayerID>& players, QWidget *parent) :
    QWidget(parent)
{

}

PlayerList::~PlayerList(){
}

const PlayerID PlayerList::pickPlayer() const
{

}

void PlayerList::updatePlayers(const BoardSnapshot& board)
{
    for(int i = 0; i < player_ids.size(); i++)
    {
        const ContainerID player_hand{std::string{"Player" + std::to_string(i+1) + "_hand"}};
        const ContainerID player_keepers{std::string{"Player" + std::to_string(i+1) + "_keepers"}};
        //CardContainer hand{board.getContainer(player_hand)};
        //CardContainer keepers{board.getContainer(player_hand)};
        //players.at(i)->updateCards(hand.getCards(), keepers.getCards());
    }
}
