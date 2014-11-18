#include <algorithm>
#include "CardContainer.h"

	void CardContainer::addCard(CardID c)
	{
		if(std::find(_cards.begin(), _cards.end(),c) == _cards.end())	//Guard for duplicates
		_cards.push_back(c);
	}

	void CardContainer::removeCard(CardID c)
	{
		_cards.erase(std::find(_cards.begin(), _cards.end(),c));	//Does not need a guard given std::find() has it's own.
	}

	const int CardContainer::getSize() const
	{
		return _cards.size();
	}

	const std::vector<CardID> CardContainer::getCards() const
	{
		return _cards;
	}

	const ContainerID CardContainer::getID() const
	{
		return _id;
	}