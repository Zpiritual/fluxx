#include "Stock.h"
#include "Deck.h"
#include "Card.h"
#include "CardID.h"
#include "ContainerID.h"
#include "Effect.h"
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int main()
{
	//Gen Deck
	vector<const Card *> cards;
	vector<Effect*> effects;
	effects.push_back(new Effect);
	for(int i =  0; i < 10; i++)
	{
		cards.push_back(new Card(CardID(i+1), "ACTION", "NUMERIC", "The card is a placeholder...", effects));
	}
	Deck *deck = new Deck(cards);
	//==
		ContainerID id1("Container 1");
	cout << "Checking pop and push..." << endl;
	Stock stock(deck->getCardIDList(), id1);
	for(int i = 0; i < 10; i++)
	{
		stock.pop();
	}
	for(int i = 0; i < 10; i++)
	{
		stock.push(cards.at(i));
	}
	cout << "Top element: " << stock.pop() << endl;
	cout << "Second element: " << stock.pop() << endl;
	cout << "Randomizing..."<<endl;
	cout << "Top element: " << stock.pop() << endl;
	return 0;
}