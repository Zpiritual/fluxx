//Autor: Martin
//Changelog:
//==========
//Made copy and move accessable
#ifndef CARDID_H
#define CARDID_H
struct CardID
{
	int val;
	CardID(int val):val{val}
	{}

	CardID() 							= delete;
	CardID(const CardID&) 				= default;
	CardID (CardID&&) 					= default;

	CardID& operator= (const CardID&) 	= default;
	CardID& operator= (CardID&&) 		= default;

	~CardID() 							= default;

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