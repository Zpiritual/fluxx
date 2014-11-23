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
#include "Player.h"
struct BoardSnapshot
{
std::vector<CardContainer> val;
std::vector<Player> play;
Direction dir;
	BoardSnapshot(std::vector<CardContainer> val, std::vector<Player> play, Direction dir);
	BoardSnapshot() = delete;
	BoardSnapshot(const BoardSnapshot&) = delete;
	BoardSnapshot (BoardSnapshot&&) = delete;

	BoardSnapshot& operator= (const BoardSnapshot&) = delete;
	BoardSnapshot& operator= (BoardSnapshot&&) = delete;

	~BoardSnapshot() = default;
    CardContainer getContainer(const CardContainerID id);
};
#endif
