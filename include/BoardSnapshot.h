//Changelog:
//=========
#ifndef BOARDSNAPSHOT_H
#define BOARDSNAPSHOT_H
#include <vector>
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

};
#endif