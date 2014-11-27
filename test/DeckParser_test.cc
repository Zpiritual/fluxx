#include <iostream>
#include "DeckParser.h"
#include "Deck.h"
using namespace std;

int main()
{
	DeckParser p;
	//Deck* deck{p.deck_to_game("discardables/Default.fluxx")};
	Deck* deck{p.deck_to_game("docs/10keepers.fluxx")};
	std::cout << "\nDeck size: " << deck->getSize() << "\nCardID list: ";

	for (auto i : deck->getCardIDList())
	{
		cout << i.val << " ";
	}
	return 0;
}