//Changelog:
//==========
//2014-11-06
//Added const to getters
//2014-11-19
//Added ID to Container
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "PlayerID.h"
#include "CardContainerID.h"
class Player
{
public:
	Player(const PlayerID pid,const CardContainerID cid, const std::string name):_id{pid}, _name{name}, _cid{cid}
	{}

	Player() = delete;
	Player(const Player&) = default;
	Player (Player&&) = default;

	Player& operator= (const Player&) = default;
	Player& operator= (Player&&) = default;

	~Player() = default;

	const std::string getName() const
	{
		return _name;
	}

	const PlayerID getID() const 
	{
		return _id;
	}

private:
	const PlayerID _id;
	const CardContainerID _cid;
	const std::string _name;
};
#endif