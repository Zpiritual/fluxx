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
	effects.push_back(new Draw(1,1,1));
	for(int i =  0; i < 10; i++)
	{
		cards.push_back(new Card(CardID(i+1), "ACTION", "NUMERIC", "The card is a placeholder...", effects));
	}
	Deck *deck = new Deck(cards);
	vector<Player> players;

	players.push_back(Player(PlayerID("player1"), CardContainerID("player1_hand"),"joe"));

	GameLogic *logic = new GameLogic(deck,players);
	logic->addEffect(effects.at(0));
	logic->nextEffect();
	return 0;
}