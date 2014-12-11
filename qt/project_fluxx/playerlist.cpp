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
    this->setAutoFillBackground(false);
    for(unsigned int i = 0; i < player_ids.size(); i++)
    {
        const CardContainerID player_hand{std::string{"Player" + std::to_string(i+1) + "_hand"}};
        const CardContainerID player_keepers{std::string{"Player" + std::to_string(i+1) + "_keepers"}};
        CardContainer hand{board->getContainer(player_hand)};
        CardContainer keepers{board->getContainer(player_keepers)};
        players.at(i)->updateCards(hand.getCards(), keepers.getCards());
    }
    updatePlayerState(board->current_player.getInt(), board->next_player.getInt());
}
void PlayerList::uiElements()
{
    vertical_layout = new QVBoxLayout();
    this->setPalette(QPalette(QPalette::Background, Qt::green));
    this->setAutoFillBackground(false);

    for(unsigned int i = 0; i < player_ids.size(); i++)
    {
        players.push_back(new PlayerListItem(player_ids.at(i)));
        vertical_layout->addWidget(players.at(i));
    }
    vertical_layout->setAlignment(players.at(player_ids.size() - 1), Qt::AlignTop);
    this->setLayout(vertical_layout);
}

void PlayerList::updatePlayerState(int player_id, int next_player_id)
{

    for(unsigned int i = 0; i < player_ids.size(); i++)
    {
        if (i == (unsigned int) player_id - 1)
        {
            players.at(i)->setActivePlayer();
        }
        else if(i == (unsigned int) next_player_id - 1)
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
    this->setAutoFillBackground(true);
    for(unsigned int i = 0; i < players.size(); i++)
    {
        QObject::connect(players.at(i), SIGNAL(clicked()), &loop, SLOT(quit()));
    }
}

PlayerID PlayerList::getPlayerId(const ProfileName player_name) const
{
    for(unsigned i = 0; i < players.size(); i++)
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
    throw std::logic_error{"Illigal! The game has more than 6 players"};
}

