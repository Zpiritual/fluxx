#include "SessionData.h"

SessionData::SessionData(
	PlayerID winning_player,
	std::vector<PlayerStats> players,
	GameState game_state,
	int elapsed_time)
    :
    winning_player{winning_player},
    players{players},
    game_state{game_state},
    elapsed_time{elapsed_time}
{}
