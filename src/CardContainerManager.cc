
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
		for(const CardID id : getCards(ccid))
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
		i.second = nullptr;
	}

	delete _stock;
	_stock = nullptr;
}

void CardContainerManager::reshuffle()
{
	_stock->shuffle();
}

void CardContainerManager::drawCard(const CardContainerID container)
{
	if(_stock->empty())
	{
		cerr << "Stock empty, reshuffling trash into stock." << endl;
		clearContainer(CardContainerID("Trash"));
		reshuffle();		
		if(_stock->empty())
		{
			cerr << "No cards to draw, tough luck!" << endl;
			return;
		}
	}

	CardID id = _stock->pop();
	getContainer(container)->addCard(id);
	notify(_stock->getID(),container,id,Event::CARD_MOVED);
}

void CardContainerManager::moveCard(const CardContainerID from, const CardContainerID to, const CardID card)
{
	getContainer(from)->removeCard(card);
	getContainer(to)->addCard(card);
	notify(from,to,card,Event::CARD_MOVED);
}

int CardContainerManager::getSize(const CardContainerID container)
{
	return getContainer(container)->getSize();
}

CardContainer* CardContainerManager::getContainer(const CardContainerID container)
{
	return _containers.at(container);
}

vector<CardID> CardContainerManager::getCards(const CardContainerID container)
{
	return getContainer(container)->getCards();
}

std::vector<CardContainer> CardContainerManager::getContainers() const
{
	std::vector<CardContainer> cardContainers;
	for(auto it = _containers.begin(); it != _containers.end(); ++it)
	{
		cardContainers.push_back(*(it->second));
	}
	return cardContainers;
}

CardID CardContainerManager::getRandomCard(const CardContainerID container)
{
	return getContainer(container)->getRandomCard();
}

void CardContainerManager::suspendCard(const CardContainerID& ccid, const CardID& cid)
{
	getContainer(ccid)->removeCard(cid);
    _suspendedCards.push(cid);
    notify(ccid, CardContainerID("SuspendedCards"),cid,Event::CARD_MOVED);
}

void CardContainerManager::unSuspendCard(const CardContainerID& ccid)
{
    if(!_suspendedCards.empty())
	{
        CardID id = _suspendedCards.top();
        getContainer(ccid)->addCard(id);
		_suspendedCards.pop();
        notify(CardContainerID("SuspendedCards"), ccid,id,Event::CARD_MOVED);

	}
    else
        throw std::logic_error("No Cards are suspended");
}
	void CardContainerManager::swapCards(const CardContainerID ccid1, const CardContainerID ccid2)
	{
		std::vector<CardID> cardIDList = getCards(ccid1);
		std::vector<CardID> cardIDList2 = getCards(ccid2);
		for(CardID id: cardIDList)
		{
			moveCard(ccid1, ccid2, id);
		}
        for(CardID id : cardIDList2)
		{
			moveCard(ccid2,ccid1,id);
		}
	}
