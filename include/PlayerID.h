//Changelog:
//==========
//Made copy and move accessable
#ifndef PLAYERID_H
#define PLAYERID_H
struct PlayerID
{
int val;
	PlayerID(int val):val{val}
	{}

	PlayerID() = delete;
	PlayerID(const PlayerID&) = default;
	PlayerID (PlayerID&&) = default;

	PlayerID& operator= (const PlayerID&) = default;
	PlayerID& operator= (PlayerID&&) = default;

	~PlayerID() = default;
 
	bool operator ==(const PlayerID &p) const
	{
		return val == p.val;
	}

	bool operator !=(const PlayerID &p) const
	{
		return val != p.val;
	}

};
#endif