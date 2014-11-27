#include "Deck.h"
#include "Card.h"
#include "CardID.h"
#include "Effect.h"
#include "GameLogic.h"
#include "Player.h"
#include "DeckParser.h"
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
	DeckParser p;

	Deck *deck = p.deck_to_game("docs/10keepers.fluxx");
	vector<Player> players;

	players.push_back(Player(PlayerID(PlayerIdentifier::Player1)));

	GameLogic *logic = new GameLogic(deck,players.size());
	cout << "SIZE OF Trash: " << logic->getCCM()->getSize(CardContainerID("Trash")) << endl;
	cout << "SIZE OF PLAYER 1 HAND: "<< logic->getCCM()->getSize(CardContainerID("Player1_hand")) << endl;
	// logic->playCard(players.at(0).getID(), CardID(10));
	// logic->playCard(players.at(0).getID(), CardID(9));
	// logic->playCard(players.at(0).getID(), CardID(8));
	cout << "SIZE OF PLAYER 1 HAND: " << logic->getCCM()->getSize(CardContainerID("Player1_hand")) << endl;
	cout << "SIZE OF Trash: " << logic->getCCM()->getSize(CardContainerID("Trash")) << endl;
	// logic->drawCard(players.at(0).getID());
	// logic->drawCard(players.at(0).getID());
	// logic->drawCard(players.at(0).getID());

	// logic->playCard(players.at(0).getID(), CardID(7));
	return 0;
}