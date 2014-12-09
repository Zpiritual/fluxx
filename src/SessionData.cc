#include "SessionData.h"

SessionData::SessionData(PlayerID winning_player, std::vector<PlayerStats> players)
    : winning_player{winning_player}, players{players}
{}
