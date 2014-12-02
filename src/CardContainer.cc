#include <algorithm>
#include <stdexcept>
#include "CardContainer.h"

void CardContainer::addCard(const CardID c)
{
	//if(std::find(_cards.begin(), _cards.end(), c) == _cards.end())	//Guard for duplicates //Nooo, bättre att kasta så vi upptäcker felet.
	_cards.push_back(c);
}

void CardContainer::removeCard(const CardID c)
{
	auto card = std::find(_cards.begin(), _cards.end(),c);

	if (card == _cards.end())
	{
		throw std::logic_error("CardContainer::removeCard(const CardID c) - Kortet existerar inte i denna container.");
	}
	_cards.erase(card);	//Does not need a guard given std::find() has it's own.
}

const int CardContainer::getSize() const
{
	return _cards.size();
}

const std::vector<CardID> CardContainer::getCards() const
{
	return _cards;
}

const CardContainerID CardContainer::getID() const
{
	return _id;
}