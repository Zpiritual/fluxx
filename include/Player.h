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
	Player(const PlayerID pid);

	Player() = delete;
	Player(const Player&) = default;
	Player (Player&&) = default;

	Player& operator= (const Player&) = default;
	Player& operator= (Player&&) = default;

	~Player() = default;

	std::string getName() const;
	PlayerID getID() const;
	int getCardsPlayed() const;
	void incrementCardsPlayed();
	void resetCardsPlayed();
	int getCardsDrawn() const;
	void incrementCardsDrawn();
	void resetCardsDrawn();

private:
	const PlayerID _id;
	int _played_cards = 0;
	int _drawn_cards = 0;
};
#endif