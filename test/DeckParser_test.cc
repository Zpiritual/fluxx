#include <iostream>
#include "DeckParser.h"
#include "Deck.h"

int main()
{
	DeckParser p;
	//Deck* deck{p.deck_to_game("discardables/Default.fluxx")};
	Deck* deck{p.deck_to_game("docs/10keepers3actions.fluxx")};
	std::cout << "\nDeck size: " << deck->getSize() << "\nCardID list: ";

	for (auto i : deck->getCardIDList())
	{
		std::cout << i.val << " ";
	}

	std::cout << endl;
	return 0;
}