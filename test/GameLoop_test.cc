#include <iostream>
#include "GameLoop.h"
#include "DeckParser.h"

using namespace std;

int main()
{
	DeckParser p;
	GameLoop gl{p.deck_to_game("/docs/10keepers.fluxx"), 2};
	//GameLoop gl{p.deck_to_game("../discardables/Default.fluxx"), 2};

	//gl.run();

	return 0;
}