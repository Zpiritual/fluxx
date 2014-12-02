#include "CardContainer.h"
#include "CardContainerManager.h"
#include "Stock.h"
//#include <map>
//#include <utility>
#include <iostream>
#include "enums.h"
#include <exception>
CardContainerManager::CardContainerManager(const Deck* deck)
// Konstruktorn skall initiera både stock-objektet och vektorn med cardcontainers.
  	{
	_stock = new Stock(CardContainerID("Stock"));

	for(CardID c:deck->getCardIDList())
		 {
		 	_stock->push(c);
		 }
	const CardContainerID trash("Trash");
	_containers.insert(std::make_pair(trash, new CardContainer(trash)));
	
    const CardContainerID goal("Goal");
    _containers.insert(std::make_pair(goal, new CardContainer(goal)));

	const CardContainerID rules("Rules");
	_containers.insert(std::make_pair(rules, new CardContainer(rules)));

	const CardContainerID temp_a("tempA");
	_containers.insert(std::make_pair(temp_a, new CardContainer(temp_a)));

	const CardContainerID temp_b("tempB");
	_containers.insert(std::make_pair(temp_b, new CardContainer(temp_b)));
	for(int i = 1; i <= 6; i++)
	{
		std::string player_container = "Player";
		player_container += '0'+ i ;
		player_container += "_hand";
		const CardContainerID container(player_container);
		_containers.insert(std::make_pair(container, new CardContainer(container)));
		//std::cout << "Container: playerID = " << container.val << std::endl;
	}

	for(int i = 1; i <= 6; i++)
	{
		char player_number = '0' + i;
		std::string player_container = "Player";
		player_container += player_number;
		player_container += "_keepers";
		const CardContainerID container(player_container);
		_containers.insert(std::make_pair(container, new CardContainer(container)));
	}	
}

void CardContainerManager::clearContainer(const  CardContainerID ccid)
{
		for(const CardID id: getCards(ccid))
			{
				getContainer(ccid)->removeCard(id);
				_stock->push(id);
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
	if(_stock->empty())
	{
		clearContainer(CardContainerID("Trash"));
	}
	getContainer(container)->addCard(_stock->pop());
	notify(_stock->getID(),container,Event::CARD_MOVED);
}

void CardContainerManager::moveCard(const CardContainerID from, const CardContainerID to, const CardID card)
{
	getContainer(from)->removeCard(card);
	getContainer(to)->addCard(card);
	notify(from,to,Event::CARD_MOVED);
}

const int CardContainerManager::getSize(const CardContainerID container)
{
	return getContainer(container)->getSize();
}

CardContainer* CardContainerManager::getContainer(const CardContainerID container)
{
	return _containers.at(container);
}

const vector<CardID> CardContainerManager::getCards(const CardContainerID container)
{
	return getContainer(container)->getCards();
}
const std::vector<CardContainer> CardContainerManager::getContainers() const
{
	std::vector<CardContainer> cardContainers;
	for(auto it = _containers.begin(); it != _containers.end(); ++it)
	{
		cardContainers.push_back(*(it->second));
	}
	return cardContainers;
}
    void CardContainerManager::unSuspendCard(const CardContainerID& ccid)
	{
        if(!_suspendedCards.empty())
		{
			getContainer(ccid)->addCard(_suspendedCards.top());
			_suspendedCards.pop();
            notify(CardContainerID("SuspendedCards"), ccid,Event::CARD_MOVED);

		}
        else
            throw std::logic_error("No Cards are suspended");
	}

    void CardContainerManager::suspendCard(const CardContainerID& ccid, const CardID& cid)
	{
		getContainer(ccid)->removeCard(cid);
        _suspendedCards.push(cid);
        notify(ccid, CardContainerID("SuspendedCards"),Event::CARD_MOVED);
	}
