//Changelog:
//==========
//2014-11-06
//Changed _cards from const
//Changed pointers from const Card const pointer to const Card pointer - impossible to use map and const pointers 
#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include "CardID.h"
#include <map>
#include <vector>
class Deck
{
public:
	Deck(const std::vector<const Card* > &cards)
	{
		for(auto a: cards)
			_cards.insert(std::pair<const CardID, const Card * >(a->getID(), a));
	}

	Deck() = delete;
	Deck(const Deck&) = default;
	Deck (Deck&&) = default;

	Deck& operator= (const Deck&) = default;
	Deck& operator= (Deck&&) = default;

	~Deck() {
	for (auto i : _cards)
		delete i.second;
	}

	const Card* const getCard(const CardID id) const
	{
		try
		{

			return _cards.at(id);
		}
		catch(...)
		{
			return nullptr;
		}
	}

private:
	std::map<const CardID, const Card* > _cards;
};
#endif