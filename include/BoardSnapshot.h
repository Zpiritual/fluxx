//Changelog:
//=========
//2014-11-18
//Added getContainer(ContainerID)
#ifndef BOARDSNAPSHOT_H
#define BOARDSNAPSHOT_H
#include <vector>
#include <algorithm>
#include "CardContainer.h"
#include "RuleManager.h"
struct BoardSnapshot
{
std::vector<CardContainer> val;
Direction dir;
	BoardSnapshot(std::vector<CardContainer> val, Direction dir):val{val}, dir{dir}
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