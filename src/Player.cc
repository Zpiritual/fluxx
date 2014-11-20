#include "Player.h"
	
	Player::Player(const PlayerID pid,const CardContainerID cid, const std::string name):_id{pid}, _name{name}, _cid{cid}
	{}
	const std::string Player::getName() const
	{
		return _name;
	}

	const PlayerID Player::getID() const 
	{
		return _id;
	}
	const CardContainerID Player::getContainerID() const
	{
		return _cid;
	}