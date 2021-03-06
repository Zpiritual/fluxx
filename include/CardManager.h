#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include "Deck.h"
#include "Card.h"
#include "CardID.h"

class CardManager
{
public:
	CardManager(const Deck* const d);
	CardManager() 								= delete;
	CardManager(const CardManager&) 			= delete;
	CardManager (CardManager&&) 				= delete;

	CardManager& operator= (const CardManager&)	= delete;
	CardManager& operator= (CardManager&&)		= delete;

	~CardManager() 								= default;

	const Card* getCard(const CardID) const;

private:
	const Deck* const _deck;
};

#endif
