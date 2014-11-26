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
	const std::vector<CardContainer> containers;
	const int players;
	const PlayerID current_player;
	const Direction direction;
	
<<<<<<< HEAD
	BoardSnapshot(const std::vector<CardContainer>, const int, const PlayerID, const Direction);
=======
	BoardSnapshot(std::vector<CardContainer> val, std::vector<Player> play,int current_player Direction dir);
>>>>>>> removed Binaries
	BoardSnapshot() = delete;
	BoardSnapshot(const BoardSnapshot&) = delete;
	BoardSnapshot (BoardSnapshot&&) = delete;

	BoardSnapshot& operator= (const BoardSnapshot&) = delete;
	BoardSnapshot& operator= (BoardSnapshot&&) = delete;

	~BoardSnapshot() = default;
    CardContainer getContainer(const CardContainerID id);
};

#endif