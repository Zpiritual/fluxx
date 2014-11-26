#include "playerlist.h"

PlayerList::PlayerList(const std::vector<PlayerID>& plyers, QWidget *parent) :
    QWidget(parent)
{
    vertical_layout = new QVBoxLayout();
    player_ids = plyers;

    current_player = -1;
    next_player = -1;

    for(int i = 0; i < player_ids.size(); i++)
    {
        players.push_back(new PlayerListItem(player_ids.at(i)));
        vertical_layout->addWidget(players.at(i));
        vertical_layout->setAlignment(players.at(i), Qt::AlignTop);
    }

    this->setLayout(vertical_layout);
}

PlayerList::~PlayerList()
{
    for(int i = 0; i < players.size(); i++)
    {
        delete players.at(i);
    }
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
//        updatePlayerState(i, board->current_player, board->dir);
    }
}

//void PlayerList::updatePlayerState(int index, const PlayerID& player_id, const Direction& direction)
//{
//    if(players.at(index)->getPlayerId() == player_id)
//    {
//        current_player = index;
//        players.at(index)->setActivePlayer();
//        if(direction == CLOCKWISE)
//        {
//            if(index == player_ids.size() - 1)
//            {
//                players.at(0)->setNextPlayer();
//                next_player = 0;
//            }
//            else
//            {
//                players.at(index+1)->setNextPlayer();
//                next_player = i+1;
//            }
//        }
//        else
//        {
//            if(index == 0)
//            {
//                players.at(player_ids.size() - 1)->setNextPlayer();
//                next_player = player_ids.size() - 1;
//            }
//            else
//            {
//                players.at(index-1)->setNextPlayer();
//                next_player = i-1;
//            }
//        }
//    }
//    else
//    {
//        if(index != current_player && index != next_player)
//        {
//            players.at(index)->setInactivePlayer();
//        }
//    }
//}
