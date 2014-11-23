#include <iostream>
#include "DeckParser.h"
#include "Deck.h"
using namespace std;

int main()
{
	DeckParser p;
	p.deck_to_game("discardables/Default.fluxx");
	return 0;
}