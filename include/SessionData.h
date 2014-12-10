//Changelog:
//==========
//2014-11-06
//Changed PlayerID* to PlayerID

#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include "Player.h"
#include "PlayerID.h"
#include <vector>

struct SessionData
{
	PlayerID winning_player;	
	std::vector<PlayerStats> players;
    GameState game_state;
	int elapsed_time; //Sekunder
	
    SessionData(PlayerID, std::vector<PlayerStats>, GameState, int);

    SessionData() = delete;
	SessionData(const SessionData&) = default;
	SessionData (SessionData&&) = default;

	SessionData& operator= (const SessionData&) = default;
	SessionData& operator= (SessionData&&) = default;

	~SessionData() = default;
};

#endif
