#include "SessionData.h"

SessionData::SessionData(PlayerID winning_player, std::vector<PlayerStats> players, GameState game_state)
    : winning_player{winning_player}, players{players}, game_state{game_state}
{}
