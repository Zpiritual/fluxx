#include <algorithm>
#include <stdexcept>
#include "CardContainer.h"

void CardContainer::addCard(const CardID c)
{
	if(c == CardID(0))
		return;
	//if(std::find(_cards.begin(), _cards.end(), c) == _cards.end())	//Guard for duplicates //Nooo, bättre att kasta så vi upptäcker felet.
	_cards.push_back(c);
}

void CardContainer::removeCard(const CardID c)
{
	if(c == CardID(0))
		return;
	auto card = std::find(_cards.begin(), _cards.end(),c);

	if (card == _cards.end())
	{
        throw std::logic_error("CardContainer::removeCard(const CardID) - Kortet existerar inte i denna container. CardID: " + c.val);
	}
    _cards.erase(card);
}

int CardContainer::getSize() const
{
	return _cards.size();
}

std::vector<CardID> CardContainer::getCards() const
{
	return _cards;
}

CardContainerID CardContainer::getID() const
{
	return _id;
}

CardID CardContainer::getRandomCard() const
{
	return _cards.at(_cards.size()-1); //Extremt slumpmässigt :)
}
