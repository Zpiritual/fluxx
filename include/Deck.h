//Changelog:
//==========
//2014-11-06
//Changed _cards from const
//Changed pointers from const Card const pointer to const Card pointer - impossible to use map and const pointers 
//2014-11-14
//Removed const from vector given <const T> not allowed
#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include "CardID.h"
#include <map>
#include <vector>
class Card;
class Deck
{
public:
	Deck(const std::vector< const Card* > &cards)
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

	const int getSize() const 
	{
		return _cards.size();
	}

	const std::vector<CardID> getCardIDList() const 
	{
		std::vector<CardID> v;
		for(auto it=_cards.begin(); it != _cards.end(); ++it)
		{
			v.push_back(it->first);
		}
		return v;
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