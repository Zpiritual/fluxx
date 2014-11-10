//Autor: Martin
//Changelog:
//==========
//Made copy and move accessable
#ifndef PLAYERID_H
#define PLAYERID_H
struct PlayerID
{
int val;
	//Can only be created with a value
	PlayerID(int val):val{val}
	{}

	//Default forbidden
	PlayerID() = delete;
	PlayerID(const PlayerID&) = default;
	PlayerID (PlayerID&&) = default;

	PlayerID& operator= (const PlayerID&) = default;
	PlayerID& operator= (PlayerID&&) = default;

	//Default Destructor
	~PlayerID() = default;

	//operators 
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