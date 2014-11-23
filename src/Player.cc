#include "Player.h"
	
Player::Player(const PlayerID pid,const CardContainerID cid):_id{pid}, _cid{cid}
{}

const PlayerID Player::getID() const 
{
	return _id;
}

const CardContainerID Player::getContainerID() const
{
	return _cid;
}