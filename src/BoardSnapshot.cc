#include "BoardSnapshot.h"


BoardSnapshot(const std::vector<CardContainer> containers,
			  const int players,
			  const PlayerID current,
			  const Direction direction)
	: containers{containers}, players{players}, current_player{current}, direction{direction}
{}

CardContainer BoardSnapshot::getContainer(const CardContainerID id)
{
	for(auto a: val)
	{
		if(a.getID() == id) return a;
	}
}
