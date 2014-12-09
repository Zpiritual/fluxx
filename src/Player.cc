#include "Player.h"
	
Player::Player(const PlayerID pid)
	: _id{pid}, _played_cards{0}, _drawn_cards{0}
{}

// std::string Player::getName() const
// {
// 	return _id.getString();
// }

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

void Player::incrementTotalCardsPlayed()
{
	++_total_played_cards;
}

void Player::incrementCardsDrawn()
{
	++_drawn_cards;
}

void Player::incrementTotalCardsDrawn()
{
	++_total_drawn_cards;
}

void Player::resetCardsPlayed()
{
	_played_cards = 0;
}

void Player::resetCardsDrawn()
{
	_drawn_cards = 0;
}

int Player::getConsecutivePlays() const
{
	return _consecutive_plays;
}

void Player::incrementConsecutivePlays()
{
	++_consecutive_plays;
}

void Player::resetConsecutivePlays()
{
	_consecutive_plays = 0;
}

int Player::getMaxConsecutivePlays() const
{
	return _max_consecutive_plays;
}

void Player::setMaxConsecutivePlays(int new_max)
{
	_max_consecutive_plays = new_max;
}

PlayerStats Player::makeStats() const
{
	return PlayerStats(_id, _total_played_cards, _total_drawn_cards, _max_consecutive_plays);
}