//Autor: Martin
//Changelog:
//==========
//Made copy and move accessable
#ifndef CARDID_H
#define CARDID_H
struct CardID
{
int val;
	//Can only be created with a value
	CardID(int val):val{val}
	{}

	//Default forbidden
	CardID() = delete;
	CardID(const CardID&) = default;
	CardID (CardID&&) = default;

	CardID& operator= (const CardID&) = default;
	CardID& operator= (CardID&&) = default;

	//Default Destructor
	~CardID() = default;

	//operators 
	bool operator ==(const CardID &p) const
	{
		return val == p.val;
	}

	bool operator !=(const CardID &p) const
	{
		return val != p.val;
	}
};
#endif