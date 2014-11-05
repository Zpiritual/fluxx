//Autor Martin
#ifndef CONTAINERID_H
#define CONTAINERID_H
#include <string>
struct ContainerID
{
std::string val;
	//Can only be created with a value
	ContainerID(std::string val):val{val}
	{}

	//Default, Move and Copy forbidden
	ContainerID() = delete;
	CardContainerID(const ContainerID&) = delete;
	ContainerID (ContainerID&&) = delete;

	ContainerID& operator= (const ContainerID&) = delete;
	ContainerID& operator= (ContainerID&&) = delete;

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