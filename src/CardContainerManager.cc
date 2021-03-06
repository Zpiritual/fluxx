
#include "CardContainer.h"
#include "CardContainerManager.h"
#include "Stock.h"
#include <iostream>
#include "enums.h"
#include <exception>

CardContainerManager::CardContainerManager(const Deck* deck)
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

	const CardContainerID temp_c("system_temp");
	_containers.insert(std::make_pair(temp_c, new CardContainer(temp_c)));

	for(int i = 1; i <= 6; i++)
	{
		std::string player_container = "Player";
		player_container += '0'+ i ;
		player_container += "_hand";
		const CardContainerID container(player_container);
		_containers.insert(std::make_pair(container, new CardContainer(container)));
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

void CardContainerManager::containerToStock(const  CardContainerID ccid)
{
	if(ccid == CardContainerID("tempA"))
		cerr << "CardContainerManager::containerToStock - Recieved container id \"tempA\"." << endl;
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
	while(!_temps.empty())
	{
		delete _temps.top();
		_temps.pop();
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
	if(container == CardContainerID("tempA"))
		cerr << "CardContainerManager::drawCard - Recieved container id \"tempA\"." << endl;
	if(_stock->empty())
	{
		containerToStock(CardContainerID("Trash"));
		reshuffle();

		if(_stock->empty())
		{
			return;
		}
	}
	CardID id = _stock->pop();
	getContainer(container)->addCard(id);
	notify(_stock->getID(), container, id, Event::CARD_MOVED);
}

void CardContainerManager::moveCard(const CardContainerID from, const CardContainerID to, const CardID card)
{
	if(from == CardContainerID("tempA"))
		cerr << "CardContainerManager::moveCard - Recieved container id \"tempA\"." << endl;
	if(card == CardID(0))
	{
		return;
	}
	getContainer(from)->removeCard(card);
	getContainer(to)->addCard(card);
	notify(from, to, card, Event::CARD_MOVED);
}

void CardContainerManager::moveCards(const CardContainerID from, const CardContainerID to)
{
	for(CardID id: getCards(from))
	{
		moveCard(from, to, id);
	}
}


int CardContainerManager::getSize(const CardContainerID container)
{
	if(container == CardContainerID("tempA"))
		cerr << "CardContainerManager::getSize - Recieved container id \"tempA\"." << endl;
	return getContainer(container)->getSize();
}

CardContainer* CardContainerManager::getContainer(const CardContainerID container)
{
	cerr << "CardContainerManager::getContainer() - Accessing container " << container.val << " in CCM." << endl;
	if(!_temps.empty() && container == CardContainerID("tempA"))
	{
		return _temps.top();
	}
	else if(container == CardContainerID("tempA"))
	{
		throw logic_error("Temp container does no exist");
	}
	return _containers.at(container);
}

vector<CardID> CardContainerManager::getCards(const CardContainerID container)
{
	if(container == CardContainerID("tempA"))
		cerr << "CardContainerManager::getCards - Recieved container id \"tempA\"." << endl;
	return getContainer(container)->getCards();
}

std::vector<CardContainer> CardContainerManager::getContainers() const
{
	std::vector<CardContainer> cardContainers;
	
	for(auto it = _containers.begin(); it != _containers.end(); ++it)
	{
        if(it->second)
		cardContainers.push_back(*(it->second));
	}

	if(!isEmptyTemp())
	{
        cardContainers.push_back(*_temps.top());
	}
	else
	{
		CardContainer cc(CardContainerID("tempA"));
		cardContainers.push_back(cc);
	}
	return cardContainers;
}

CardID CardContainerManager::getRandomCard(const CardContainerID container)
{
	if(container == CardContainerID("tempA"))
		cerr << "CardContainerManager::getRandomCard - Recieved container id \"tempA\"." << endl;
	return getContainer(container)->getRandomCard();
}

void CardContainerManager::suspendCard(const CardContainerID& ccid, const CardID& cid)
{
	if(ccid == CardContainerID("tempA"))
		cerr << "CardContainerManager::suspendCard - Recieved container id \"tempA\"." << endl;
	if(cid == CardID(0))
	{
		return;
	}
	getContainer(ccid)->removeCard(cid);
	_suspendedCards.push(cid);
	notify(ccid, CardContainerID("SuspendedCards"),cid,Event::CARD_MOVED);
}

CardID CardContainerManager::getSuspendedCard()
{
	if(!_suspendedCards.empty())
	{
		return _suspendedCards.top();
	}
	else
	{
		return CardID(0);
	}
}

bool CardContainerManager::hasSuspendedCard()
{
	return !_suspendedCards.empty();
}

void CardContainerManager::unSuspendCard(const CardContainerID& ccid)
{
	if(ccid == CardContainerID("tempA"))
		cerr << "CardContainerManager::unSuspendCard - Recieved container id \"tempA\"." << endl;
	if(!_suspendedCards.empty())
	{
		CardID id = _suspendedCards.top();
		getContainer(ccid)->addCard(id);
		_suspendedCards.pop();
		notify(CardContainerID("SuspendedCards"), ccid,id,Event::CARD_MOVED);
	}	
}

void CardContainerManager::swapCards(const CardContainerID container1, const CardContainerID container2)
{
	
	std::vector<CardID> cardIDList1 = getCards(container1);
	std::vector<CardID> cardIDList2 = getCards(container2);
	
	for(CardID id: cardIDList1)
	{
		moveCard(container1, container2, id);
	}

	for(CardID id : cardIDList2)
	{
		moveCard(container2, container1, id);
	}
}

CardContainerID CardContainerManager::newTemp()
{
	CardContainerID id("tempA");
	CardContainer* c = new CardContainer(id);
	_temps.push(c);
	return id;
}

CardContainerID CardContainerManager::getTemp() const
{
	if(_temps.empty())
	{
		throw std::logic_error("CardContainerManager::getTemp() - No temp container found.");
	}
	return _temps.top()->getID();
}

void CardContainerManager::deleteTemp()
{
	delete _temps.top();
	_temps.pop();
}

bool CardContainerManager::isEmptyTemp() const
{
	return _temps.empty();
}
