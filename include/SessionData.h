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
	std::vector<Player> val;
	//Winning players ID 
	PlayerID wp;	
	
	SessionData(std::vector<Player> val, PlayerID wp);

    SessionData() = delete;
	SessionData(const SessionData&) = default;
	SessionData (SessionData&&) = default;

	SessionData& operator= (const SessionData&) = default;
	SessionData& operator= (SessionData&&) = default;

	~SessionData() = default;
};

#endif
