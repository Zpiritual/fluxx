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
	Player(const PlayerID pid,const CardContainerID player_hand);

	Player() = delete;
	Player(const Player&) = default;
	Player (Player&&) = default;

	Player& operator= (const Player&) = default;
	Player& operator= (Player&&) = default;

	~Player() = default;

	const std::string getName() const
	{
		return _id.val;
	}

	const PlayerID getID() const;
	const CardContainerID getContainerID() const;
	const int getPlayedCards() const;
	void incrementPlayedCards();
	void resetPlayedCards();

private:
	const PlayerID _id;
	const CardContainerID _cid;
	int _played_cards;
};
#endif