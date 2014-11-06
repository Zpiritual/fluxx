//Changelog:
//==========
#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include "CardID.h"
#include <map>
#include <vector>
class Deck
{
public:
	Deck(const std::vector<const Card* const> &cards)
	{
		//for(auto a: cards)
			//_cards.[a.getID()] = a;
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
		return _cards.at(id);
	}

private:
	const std::map<const CardID, const Card* const> _cards;
};
#endif