#ifndef DECKPARSER_H
#define DECKPARSER_H
#include "Deck.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class DeckParser
{
public:
	Deck* deck_to_game(string filename);
};

#endif