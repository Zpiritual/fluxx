#include "Player.h"
	
Player::Player(const PlayerID pid)
	: _id{pid}
{}

const std::string Player::getName() const
{
	return _id.getString();
}

const PlayerID Player::getID() const 
{
	return _id;
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