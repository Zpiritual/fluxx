#include "BoardSnapshot.h"

BoardSnapshot::BoardSnapshot(const std::vector<CardContainer> containers,
			  const int players,
			  const PlayerID current,
			  const int played,
              const int to_play,
			  const Direction direction)
	: containers{containers},
	players{players},
	current_player{current},
	cards_played{played},
	cards_to_play{to_play},
	direction{direction}
{}

CardContainer BoardSnapshot::getContainer(const CardContainerID id)
{
    for(auto a: containers)
	{
		if(a.getID() == id) return a;
	}
}
