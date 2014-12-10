#include "BoardSnapshot.h"
#include <exception>

BoardSnapshot::BoardSnapshot(const std::vector<CardContainer> containers,
							 const int players,
							 const PlayerID current,
							 const PlayerID active,
							 const PlayerID next,
			 				 const int played,
			 				 const int to_play,
                             const Direction direction,
			 				 const CardContainerID target,
                             const std::vector<std::pair<const PlayerID,const std::string>>& log)
	: containers{containers},
	players{players},
	current_player{current},
	active_player{active},
	next_player{next},
	cards_played{played},
	cards_to_play{to_play},
	direction{direction},
	target_container{target},
	log{log}
{}

CardContainer BoardSnapshot::getContainer(const CardContainerID id) const
{
	for(auto a : containers)
	{
		if(a.getID() == id) return a;
	}
    throw std::logic_error("No container found with ID: " + id.val);
}
