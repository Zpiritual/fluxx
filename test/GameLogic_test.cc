#include "Deck.h"
#include "Card.h"
#include "CardID.h"
#include "Effect.h"
#include "GameLogic.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
	vector<const Card *> cards;
	vector<Effect> effects;

	for(int i =  0; i < 10; i++)
	{
		effects.push_back(Effect{"test string"});
		cards.push_back(new Card(CardID(i+1), (i < 8)?"ACTION":"RULE", "NUMERIC", "The card is a placeholder...", effects));
	}
	Deck *deck = new Deck(cards);
	vector<Player> players;

	players.push_back(Player(PlayerID(PlayerIdentifier::Player1), CardContainerID("Player1_hand")));

	GameLogic *logic = new GameLogic(deck,players);
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