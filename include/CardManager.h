//Changelog:
//2014-11-06
//Basic setup. Constructors and data members.
//==========
#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include "Deck.h"
#include "Card.h"
#include "CardID.h"

class CardManager {
public:
	ContainerID(const Deck* const d) : _deck{d}
	{}

	ContainerID() 								= delete;
	CardContainerID(const ContainerID&) 		= delete;
	ContainerID (ContainerID&&) 				= delete;

	ContainerID& operator= (const ContainerID&)	= delete;
	ContainerID& operator= (ContainerID&&)		= delete;

	~ContainerID() 								= default;

	Card* getCard(const CardID cid) { return _deck->getCard(cid) }

private:
	const Deck* const _deck;
};

#endif