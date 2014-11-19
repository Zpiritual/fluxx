#include "CardContainer.h"
#include "CardContainerManager.h"

CardContainerManager::CardContainerManager(const Deck* deck)
	// Konstruktorn skall initiera både stock-objektet och vektorn med cardcontainers.
	{

	_stock = new Stock(deck, CardContainerID("stock"));
		//Player hands
		for(int i = 1; i <= 6; i++)
		{
			char cc = i - '0';
			std::string c = "player";
			c += cc;
			c += "_hand";
			const CardContainerID cid(c);
			_containers[cid] = new CardContainer(cid);
		}

		//Trash hands
		{
			const CardContainerID cid("trash_heap");
			_containers[cid] = new CardContainer(cid);
		}

		//etc...

	}
CardContainerManager::~CardContainerManager()
	{
		for(std::pair<CardContainerID, CardContainer*> i: _containers)
		{
			delete i.second;
		}
		delete _stock;
	}
void CardContainerManager::reshuffle()
{
	_stock->shuffle();
}

void CardContainerManager::drawCard(const CardContainerID cid)
{
	getContainer(cid)->addCard(_stock->pop());
}

void CardContainerManager::moveCard(const CardContainerID from, const CardContainerID to, const CardID card)
{
	getContainer(from)->removeCard(card);
	getContainer(to)->addCard(card);
}

const int CardContainerManager::getSize(const CardContainerID container)
{
	getContainer(container)->getSize();
}

CardContainer* CardContainerManager::getContainer(const CardContainerID container)
{
	return _containers.at(container);
}

const vector<CardID> CardContainerManager::getCards(const CardContainerID container)
{
	return getContainer(container)->getCards();
}

