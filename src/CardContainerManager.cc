#include "CardContainer.h"
#include "CardContainerManager.h"
#include "Stock.h"
//#include <map>
//#include <utility>

CardContainerManager::CardContainerManager(const Deck* deck)
// Konstruktorn skall initiera både stock-objektet och vektorn med cardcontainers.
{
	_stock = new Stock(deck, CardContainerID("Stock"));

	const CardContainerID trash("Trash");
	_containers.insert(std::make_pair(trash, new CardContainer(trash)));

	const CardContainerID rules("Rules");
	_containers.insert(std::make_pair(rules, new CardContainer(rules)));

	const CardContainerID temp_a("tempA");
	_containers.insert(std::make_pair(temp_a, new CardContainer(temp_a)));

	const CardContainerID temp_b("tempB");
	_containers.insert(std::make_pair(temp_b, new CardContainer(temp_b)));

	for(int i = 1; i <= 6; i++)
	{
		char player_number = i - '0';
		std::string player_container = "Player";
		player_container += player_number;
		player_container += "_hand";
		const CardContainerID container(player_container);
		_containers.insert(std::make_pair(container, new CardContainer(container)));
	}

	for(int i = 1; i <= 6; i++)
	{
		char player_number = i - '0';
		std::string player_container = "Player";
		player_container += player_number;
		player_container += "_keepers";
		const CardContainerID container(player_container);
		_containers.insert(std::make_pair(container, new CardContainer(container)));
	}	
}

CardContainerManager::~CardContainerManager()
{
	for(std::pair<CardContainerID, CardContainer*> i : _containers)
	{
		delete i.second;
	}
	delete _stock;
}

void CardContainerManager::reshuffle()
{
	_stock->shuffle();
}

void CardContainerManager::drawCard(const CardContainerID container)
{
	getContainer(container)->addCard(_stock->pop());
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

