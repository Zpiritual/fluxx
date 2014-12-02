#include "playerlist.h"

PlayerList::PlayerList(const std::vector<ProfileName> plyers, QWidget *parent) :
    QWidget(parent)
{
    player_ids = plyers;
    current_player = -1;
    next_player = -1;

    uiElements();
}

PlayerList::~PlayerList()
{
    for(unsigned int i = 0; i < players.size(); i++)
    {
        delete players.at(i);
    }
    delete vertical_layout;
}

void PlayerList::updatePlayers(const BoardSnapshot* const board)
{
    qDebug() << "You're in updateplayers in playerlist, congratulations!";
    for(unsigned int i = 0; i < player_ids.size(); i++)
    {
        const CardContainerID player_hand{std::string{"Player" + std::to_string(i+1) + "_hand"}};
        const CardContainerID player_keepers{std::string{"Player" + std::to_string(i+1) + "_keepers"}};
        CardContainer hand{board->getContainer(player_hand)};
        CardContainer keepers{board->getContainer(player_keepers)};
        players.at(i)->updateCards(hand.getCards(), keepers.getCards());
    }
    updatePlayerState(board->current_player.getInt(), board->direction);
}

void PlayerList::updatePlayerVariables(int index, int player_id, const Direction direction)
{
    if(index == (player_id - 1))
    {
        current_player = index;
        if(direction == Direction::CLOCKWISE)
        {
            next_player = (current_player + 1) % player_ids.size();
        }
        else
        {
            if(index == 0)
            {
                next_player = player_ids.size() - 1;
            }
            else
            {
                next_player = current_player - 1;
            }
        }
    }
}

void PlayerList::uiElements()
{
    vertical_layout = new QVBoxLayout();

    for(unsigned int i = 0; i < player_ids.size(); i++)
    {
        players.push_back(new PlayerListItem(player_ids.at(i)));
        vertical_layout->addWidget(players.at(i));
        vertical_layout->setAlignment(players.at(i), Qt::AlignTop);
    }

    this->setLayout(vertical_layout);
}

void PlayerList::updatePlayerState(int player_id, const Direction direction)
{
    for(unsigned int i = 0; i < player_ids.size(); i++)
    {
        updatePlayerVariables(i, player_id, direction);
    }

    for(unsigned int i = 0; i < player_ids.size(); i++)
    {
        if (i == (unsigned int) current_player)
        {
            players.at(i)->setActivePlayer();
        }
        else if(i == (unsigned int) next_player)
        {
            players.at(i)->setNextPlayer();
        }
        else
        {
            players.at(i)->setInactivePlayer();
        }
    }
}

void PlayerList::setConnections(const PlayerLoop& loop)
{
    for(unsigned int i = 0; i < players.size(); i++)
    {
        QObject::connect(players.at(i), SIGNAL(clicked()), &loop, SLOT(quit()));
    }
}

const PlayerID PlayerList::getPlayerId(const ProfileName player_name) const
{
    for(unsigned int i = 0; i < players.size(); i++)
    {
        if(players.at(i)->getPlayerName() == player_name)
        {
            switch(i)
            {
                case 0:
                return PlayerID(PlayerIdentifier::Player1);
                case 1:
                return PlayerID(PlayerIdentifier::Player2);
                case 2:
                return PlayerID(PlayerIdentifier::Player3);
                case 3:
                return PlayerID(PlayerIdentifier::Player4);
                case 4:
                return PlayerID(PlayerIdentifier::Player5);
                case 5:
                return PlayerID(PlayerIdentifier::Player6);
            }
        }
    }
}
