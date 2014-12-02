#include "Player.h"
	
Player::Player(const PlayerID pid)
	: _id{pid}, _played_cards{0}, _drawn_cards{0}
{}

std::string Player::getName() const
{
	return _id.getString();
}

PlayerID Player::getID() const
{
	return _id;
}

int Player::getCardsPlayed() const
{
	return _played_cards;
}

int Player::getCardsDrawn() const
{
	return _drawn_cards;
}

void Player::incrementCardsPlayed()
{
	++_played_cards;
}

void Player::incrementCardsDrawn()
{
	++_drawn_cards;
}

void Player::resetCardsPlayed()
{
	_played_cards = 0;
}

void Player::resetCardsDrawn()
{
	_drawn_cards = 0;
}