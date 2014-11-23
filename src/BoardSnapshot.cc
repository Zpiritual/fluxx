#include "BoardSnapshot.h"

BoardSnapshot::BoardSnapshot(std::vector<CardContainer> val, std::vector<Player> play, Direction dir):
val{val},play{play}, dir{dir}
{}

CardContainer BoardSnapshot::getContainer(const ContainerID id)
{
for(auto a: val)
	if(a.getID() == id) return a;
}