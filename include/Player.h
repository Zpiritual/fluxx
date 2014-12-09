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
	void incrementTotalCardsPlayed();
	void resetCardsPlayed();

	int getCardsDrawn() const;
	void incrementCardsDrawn();
	void incrementTotalCardsDrawn();
	void resetCardsDrawn();
	
	int getConsecutivePlays() const;
	void incrementConsecutivePlays();
	void resetConsecutivePlays();
	
	int getMaxConsecutivePlays() const;
	void setMaxConsecutivePlays(int);

	void addLogEntry();

private:
	const PlayerID _id;

	//Dessa två nollställs i slutet av varje runda
	int _played_cards = 0;
	int _drawn_cards = 0;
	int _consecutive_plays = 0;

	//De här räknar totalt, för att spara statistik efter spelrundan.
	int _total_played_cards = 0;
	int _total_drawn_cards = 0;
	int _max_consecutive_plays = 0;
};
#endif