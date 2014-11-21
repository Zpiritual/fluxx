#include "Deck.h"
#include "Card.h"
#include "CardID.h"
#include "Effect.h"
#include "Draw.h"
#include "GameLogic.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
	vector<const Card *> cards;
	vector<Effect*> effects;

	for(int i =  0; i < 10; i++)
	{
		effects.push_back(new Draw(1,i,1));
		cards.push_back(new Card(CardID(i+1), "ACTION", "NUMERIC", "The card is a placeholder...", effects));
	}
	Deck *deck = new Deck(cards);
	vector<Player> players;

	players.push_back(Player(PlayerID("player1"), CardContainerID("Player1_hand")));

	GameLogic *logic = new GameLogic(deck,players);
	cout << logic->getCCM()->getSize(CardContainerID("Trash")) << endl;
	cout << logic->getCCM()->getSize(CardContainerID("Player1_hand")) << endl;
	logic->playCard(players.at(0).getID(), CardID(9));
	cout << logic->getCCM()->getSize(CardContainerID("Player1_hand")) << endl;
	cout << logic->getCCM()->getSize(CardContainerID("Trash")) << endl;
	logic->drawCard(players.at(0).getID());
	logic->playCard(players.at(0).getID(), CardID(6));
	return 0;
}