#include "BoardSnapshot.h"

BoardSnapshot::BoardSnapshot(std::vector<CardContainer> val, std::vector<Player> play, Direction dir, int current_player):
  val{val},play{play}, dir{dir}, current_player{current_player}
{}

CardContainer BoardSnapshot::getContainer(const CardContainerID id)
{
	for(auto a: val)
	{
		if(a.getID() == id) return a;
	}
}
