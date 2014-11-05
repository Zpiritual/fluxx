//Autor Martin
#ifndef CARDCONTAINER_ID
#define CARDCONTAINER_ID
#include <string>
struct CardContainerID
{
std::string val;
	//Can only be created with a value
	CardContainerID(std::string val):val{val}
	{}

	//Default, Move and Copy forbidden
	CardContainerID() = delete;
	CardContainerID(const CardContainerID&) = delete;
	CardContainerID (CardContainerID&&) = delete;

	CardContainerID& operator= (const CardContainerID&) = delete;
	CardContainerID& operator= (CardContainerID&&) = delete;

	//Default Destructor
	~CardContainerID() = default;

	//operators 
	bool operator ==(const CardContainerID &p) const
	{
		return val == p.val;
	}

	bool operator !=(const CardContainerID &p) const
	{
		return val != p.val;
	}
};
#endif