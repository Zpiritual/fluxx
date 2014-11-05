//Autor Martin
#ifndef CARD_ID
#define CARD_ID
struct CardID
{
int val;
	//Can only be created with a value
	CardID(int val):val{val}
	{}

	//Default, Mode and Copy forbidden
	CardID() = delete;
	CardID(const CardID&) = delete;
	CardID (CardID&&) = delete;

	CardID& operator= (const CardID&) = delete;
	CardID& operator= (CardID&&) = delete;

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