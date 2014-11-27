#include "BoardSnapshot.h"
#include <iostream>

void printBoardSnapshot(BoardSnapshot*);

int main()
{
	std::vector<CardContainer> cc1{CardContainer(CardContainerID("container1")),
									CardContainer(CardContainerID("container2"))};

	BoardSnapshot bs1{cc1, 2, PlayerID(PlayerIdentifier::Player2), 3, 4, Direction::CLOCKWISE};
	printBoardSnapshot(&bs1);

	std::vector<CardContainer> cc2{CardContainer(CardContainerID("container1")),
									CardContainer(CardContainerID("container2")),
									CardContainer(CardContainerID("container3")),
									CardContainer(CardContainerID("container4"))};

	BoardSnapshot bs2{cc2, 4, PlayerID(PlayerIdentifier::Player6), 7, 2, Direction::COUNTERCLOCKWISE};
	printBoardSnapshot(&bs2);

	return 0;
}

void printBoardSnapshot(BoardSnapshot* out)
{
	std::cout << "\nPrinting sample snapshot...\n"
		<< "\nPlayers: " << out->players
		<< "\nCurrent player: " << out->current_player.getString()
		<< "\nCards played: " << out->cards_played
		<< "\nCards to play: " << out->cards_to_play
		<< "\nPlay direction: ";

	if( out->direction == Direction::CLOCKWISE )
	{
		std::cout << "CLOCKWISE";
	}
	else if( out->direction == Direction::COUNTERCLOCKWISE )
	{
		std::cout << "COUNTERCLOCKWISE";
	}

	std::cout << "\nContainers: ";

	for (auto i : out->containers)
	{
		std::cout << i.getID().val << " ";
	}

	std::cout << std::endl;
}