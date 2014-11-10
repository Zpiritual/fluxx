//Autor: Martin
//Changelog:
//==========
//Made copy and move accessable
#ifndef CONTAINERID_H
#define CONTAINERID_H
#include <string>
struct ContainerID
{
std::string val;
	//Can only be created with a value
	ContainerID(std::string val):val{val}
	{}

	//Default forbidden
	ContainerID() = delete;
	CardContainerID(const ContainerID&) = default;
	ContainerID (ContainerID&&) = default;

	ContainerID& operator= (const ContainerID&) = default;
	ContainerID& operator= (ContainerID&&) = default;

	//Default Destructor
	~ContainerID() = default;

	//operators 
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