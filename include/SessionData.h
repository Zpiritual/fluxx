//Changelog:
//==========
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
	//Can only be created with values
	SessionData(std::vector<Player> val, PlayerID wp):val{val}, wp{wp}
	{}

	//Default, Move and Copy forbidden
	SessionData() = delete;
	SessionData(const SessionData&) = delete;
	SessionData (SessionData&&) = delete;

	SessionData& operator= (const SessionData&) = delete;
	SessionData& operator= (SessionData&&) = delete;

	//Default Destructor
	~SessionData() = default;
};
#endif