#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include "PlayerID.h"

struct PlayerStats
{
	const PlayerID _id;
	const int _total_played_cards;
	const int _total_drawn_cards;
	const int _max_consecutive_plays;

	PlayerStats(const PlayerID id, const int played, const int drawn, const int plays) :
		_id{id},
		_total_played_cards{played},
		_total_drawn_cards{drawn},
		_max_consecutive_plays{plays}
		{}
	
	PlayerStats() = default;
    PlayerStats(const PlayerStats&) = default;
    PlayerStats (PlayerStats&&) = default;

    PlayerStats& operator= (const PlayerStats&) = default;
    PlayerStats& operator= (PlayerStats&&) = default;
};

#endif
