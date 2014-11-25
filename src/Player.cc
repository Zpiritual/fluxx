#include "Player.h"
	
Player::Player(const PlayerID pid,const CardContainerID cid)
	: _id{pid}, _cid{cid}
{}

const std::string Player::getName() const
{
	return _id.val;
}

const PlayerID Player::getID() const 
{
	return _id;
}

const CardContainerID Player::getContainerID() const
{
	return _cid;
}

const int Player::getCardsPlayed() const
{
	return _played_cards;
}

void Player::incrementCardsPlayed()
{
	++_played_cards;
}

void Player::resetCardsPlayed()
{
	_played_cards = 0;
}