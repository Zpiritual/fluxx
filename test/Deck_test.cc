#include "Deck.h"
#include "Card.h"
#include "CardID.h"
#include "Effect.h"
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
	vector<const Card *> cards;
	vector<Effect> effects;
	effects.push_back(Effect{"test string"});
	
	for(int i =  0; i < 10; i++)
	{
		cards.push_back(new Card(CardID(i+1), "TEST CARD", "ACTION", "NUMERIC", "The card is a placeholder...", effects));
	}
	
	Deck deck(cards);
	cout << "Checking IDs from 1 to 20..." << endl;
	
	for(int i =  0; i < 20; i++)
	{
		assert(i < 10 ? deck.getCard(CardID(i+1)) != nullptr : deck.getCard(CardID(i+1)) == nullptr );
	}
	
	cout << "Sanity check error handling OK" << endl;
	cout << "Checking ID List... " << endl;
	assert(deck.getCardIDList().size() == 10);
	
	for(int i = 0; i < 10 ; i++)
	{
		assert(deck.getCardIDList().at(i) == cards.at(i)->getID());
	}
	
	cout << "Sanity check list size OK\n";

	return 0;
}