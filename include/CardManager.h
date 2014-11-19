//Changelog:
//2014-11-06
//Basic setup. Constructors and data members.
//Fixed misplaced Return and const statments
//==========
#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include "Deck.h"
#include "Card.h"
#include "CardID.h"

class CardManager {
public:
	CardManager(const Deck* const d) : _deck{d}
	{}

	CardManager() 								= delete;
	CardManager(const CardManager&) 			= delete;
	CardManager (CardManager&&) 				= delete;

	CardManager& operator= (const CardManager&)	= delete;
	CardManager& operator= (CardManager&&)		= delete;

	~CardManager() 								= default;

	const Card* const getCard(const CardID cid) const { return _deck->getCard(cid); }

private:
	const Deck* const _deck;
};

#endif