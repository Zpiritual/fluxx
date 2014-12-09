#include "SessionData.h"

SessionData::SessionData(PlayerID winning_player, std::vector<Player> players)
    : winning_player{winning_player}, players{players}
{}
