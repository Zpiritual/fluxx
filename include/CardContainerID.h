//Changelog:
//==========
//2014-11-06
//Made copy and move accessable
//2014-11-18
//Renamed from ContainerID to CardContainerID

#ifndef CARDCONTAINERID_H
#define CARDCONTAINERID_H

#include <string>

struct CardContainerID
{
	std::string val;
	
	CardContainerID(std::string val):val{val}
	{}

	CardContainerID()									= delete;
	CardContainerID(const CardContainerID&) 			= default;
	CardContainerID (CardContainerID&&) 				= default;

	CardContainerID& operator= (const CardContainerID&) = default;
	CardContainerID& operator= (CardContainerID&&) 		= default;

	~CardContainerID() = default;

	bool operator ==(const CardContainerID &p) const
	{
		return val == p.val;
	}

	bool operator !=(const CardContainerID &p) const
	{
		return val != p.val;
	}
	bool operator<(const CardContainerID &p) const
	{
		return val < p.val;
	}
};

#endif