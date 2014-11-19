//Changelog
//=========
//2014-11-19
//Changed _containers to _containers with *

#ifndef CARDCONTAINERMANAGER_H
#define CARDCONTAINERMANAGER_H

#include "CardContainerID.h"
#include "CardContainer.h"
#include "Deck.h"
#include "Stock.h"
#include <vector>
#include <map>
#include <string>
class Stock;
class Deck;
class CardContainerManager {
public:
	CardContainerManager(const Deck*);

	CardContainerManager() 											= delete;
	CardContainerManager(const CardContainerManager&) 				= delete;
	CardContainerManager(CardContainerManager&&) 					= delete;

	CardContainerManager& operator= (const CardContainerManager&)	= delete;
	CardContainerManager& operator= (CardContainerManager&&)		= delete;

	~CardContainerManager();

	//const CardID popDeck(); 
	// Kan nog tas bort helt, verkar överflödig.
	void reshuffle();
	void drawCard(const CardContainerID);
	void moveCard(const CardContainerID, const CardContainerID, const CardID);
	const int getSize(const CardContainerID);
	const std::vector<CardID> getCards(const CardContainerID);

private:

	Stock* _stock;
	//vector<CardContainer> _containers;
	std::map<CardContainerID, CardContainer*> _containers;
		CardContainer* getContainer(const CardContainerID);
};

#endif