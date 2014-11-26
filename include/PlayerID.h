//Changelog:
//==========
//2014-11-06
//Made copy and move accessable
//Changed != operator to inverse of ==
//Added < operator
//2014-11-19
//Changed val to string

#ifndef PLAYERID_H
#define PLAYERID_H

#include <string>
#include "enums.h"

struct PlayerID
{
	PlayerIdentifier val;
	
	PlayerID(PlayerIdentifier val) : val{val}
	{}

	PlayerID() = delete;
	PlayerID(const PlayerID&) = default;
	PlayerID (PlayerID&&) = default;

	PlayerID& operator= (const PlayerID&) = default;
	PlayerID& operator= (PlayerID&&) = default;

	~PlayerID() = default;
 
	std::string getString() const
	{
		if (val == PlayerIdentifier::Player1)
			return "Player1";
		if (val == PlayerIdentifier::Player2)
			return "Player2";
		if (val == PlayerIdentifier::Player3)
			return "Player3";
		if (val == PlayerIdentifier::Player4)
			return "Player4";
		if (val == PlayerIdentifier::Player5)
			return "Player5";
		else
			return "Player6";
	}

	bool operator ==(const PlayerID &p) const
	{
		return val == p.val;
	}

	bool operator !=(const PlayerID &p) const
	{
		return !(*this == p);
	}

	bool operator <(const PlayerID &p) const
	{
		return val < p.val;
	}
};

#endif