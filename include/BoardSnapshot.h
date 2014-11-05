//Autor Martin
#ifndef BOARDSNAPSHOT_H
#define BOARDSNAPSHOT_H
#include <vector>
#include "CardContainer.h"
struct BoardSnapshot
{
std::vector<CardContainer> val;
	//Can only be created with a value
	BoardSnapshot(std::vector<CardContainer> val):val{val}
	{}

	//Default, Move and Copy forbidden
	BoardSnapshot() = delete;
	BoardSnapshot(const BoardSnapshot&) = delete;
	BoardSnapshot (BoardSnapshot&&) = delete;

	BoardSnapshot& operator= (const BoardSnapshot&) = delete;
	BoardSnapshot& operator= (BoardSnapshot&&) = delete;

	//Default Destructor
	~BoardSnapshot() = default;

};
#endif