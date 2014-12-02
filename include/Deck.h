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

class Deck
{
public:
	Deck(const std::vector< const Card* > &cards);

	Deck() = delete;
	Deck(const Deck&) = default;
	Deck (Deck&&) = default;

	Deck& operator= (const Deck&) = default;
	Deck& operator= (Deck&&) = default;

	~Deck();

	int getSize() const;
	std::vector<CardID> getCardIDList() const ;

	const Card* getCard(const CardID id) const;

private:
	std::map<const CardID, const Card* > _cards;
};

#endif