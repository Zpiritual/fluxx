#include <algorithm>
#include "CardContainer.h"
	void CardContainer::addCard(CardID * c)
	{
		if(std::find(_cards.begin(), _cards.end(),c) == _cards.end())	//Guard for duplicates
		_cards.push_back(c);
	}

	void CardContainer::removeCard(CardID * c)
	{
		_cards.erase(std::find(_cards.begin(), _cards.end(),c));	//Odes not need a guard given std::find() has it's own.
	}

	int CardContainer::getSize()
	{
		return _cards.size();
	}

	std::vector<CardID*> CardContainer::getCards()
	{
		return _cards;
	}

	ContainerID* CardContainer::getID()
	{
		return _id;
	}