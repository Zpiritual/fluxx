//Changelog:
//=========
//2014-11-18
//Added getContainer(ContainerID)
#ifndef BOARDSNAPSHOT_H
#define BOARDSNAPSHOT_H
#include <vector>
#include <algorithm>
#include "CardContainer.h"
struct BoardSnapshot
{
std::vector<CardContainer> val;

	BoardSnapshot(std::vector<CardContainer> val):val{val}
	{}
	BoardSnapshot() = delete;
	BoardSnapshot(const BoardSnapshot&) = delete;
	BoardSnapshot (BoardSnapshot&&) = delete;

	BoardSnapshot& operator= (const BoardSnapshot&) = delete;
	BoardSnapshot& operator= (BoardSnapshot&&) = delete;

	~BoardSnapshot() = default;
	CardContainer getContainer(const ContainerID id)
	{
	for(auto a: val)
		if(a.getID() == id) return a;
	}
};
#endif