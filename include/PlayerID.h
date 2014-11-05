//Autor Martin
#ifndef PLAYERID_H
#define PLAYERID_H
struct PlayerID
{
int val;
	//Can only be created with a value
	PlayerID(int val):val{val}
	{}

	//Default, Mode and Copy forbidden
	PlayerID() = delete;
	PlayerID(const PlayerID&) = delete;
	PlayerID (PlayerID&&) = delete;

	PlayerID& operator= (const PlayerID&) = delete;
	PlayerID& operator= (PlayerID&&) = delete;

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