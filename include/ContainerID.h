//Changelog:
//==========
//14-11-6 Made copy and move accessable
#ifndef CONTAINERID_H
#define CONTAINERID_H
#include <string>
struct ContainerID
{
std::string val;
	ContainerID(std::string val):val{val}
	{}

	ContainerID()					= delete;
	ContainerID(const ContainerID&) = default;
	ContainerID (ContainerID&&) 	= default;

	ContainerID& operator= (const ContainerID&) = default;
	ContainerID& operator= (ContainerID&&) 		= default;

	~ContainerID() = default;

	bool operator ==(const ContainerID &p) const
	{
		return val == p.val;
	}

	bool operator !=(const ContainerID &p) const
	{
		return val != p.val;
	}
};
#endif