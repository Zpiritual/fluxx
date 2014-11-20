//Changelog:
//2014-11-06
//Basic setup. Constructors and data members.
//Fixed misplaced Return and const statments
//2014--11-20
//moved constructor and destructor to .cc
//added forward declarations
//==========
#ifndef CARDMANAGER_H
#define CARDMANAGER_H
#include "Deck.h"
#include "Card.h"
#include "CardID.h"
class Card;
class CardManager {
public:
	CardManager(const Deck* const d);
	CardManager() 								= delete;
	CardManager(const CardManager&) 			= delete;
	CardManager (CardManager&&) 				= delete;

	CardManager& operator= (const CardManager&)	= delete;
	CardManager& operator= (CardManager&&)		= delete;

	~CardManager() 								= default;

	const Card* const getCard(const CardID) const;

private:
	const Deck* const _deck;
};

#endif