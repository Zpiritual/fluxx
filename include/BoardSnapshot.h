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
#include "PlayerID.h"

struct BoardSnapshot
{
	const std::vector<CardContainer> containers;
	const int players;
	const PlayerID current_player;
	const int cards_played;
	const int cards_to_play;
	const Direction direction;

    BoardSnapshot(const std::vector<CardContainer>, const int, const PlayerID, const int, const int, const Direction);
	BoardSnapshot() = delete;
	BoardSnapshot(const BoardSnapshot&) = default;
	BoardSnapshot (BoardSnapshot&&) = default;

	BoardSnapshot& operator= (const BoardSnapshot&) = delete;
	BoardSnapshot& operator= (BoardSnapshot&&) = delete;

	~BoardSnapshot() = default;

	CardContainer getContainer(const CardContainerID id) const;
};

#endif
