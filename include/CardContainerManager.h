//Changelog
//=========
//2014-11-19
//Changed _containers to _containers with *
//changed stock to stock*
//moved constructor and destructor to .cc
//added forward declarations
#ifndef CARDCONTAINERMANAGER_H
#define CARDCONTAINERMANAGER_H

#include "CardContainerID.h"
#include "CardContainer.h"
#include "Deck.h"
#include "Stock.h"
#include <vector>
#include <map>
#include <string>

class CardContainerManager {
public:
	CardContainerManager(const Deck* const);

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
	CardContainer* getContainer(const CardContainerID);
	Stock* _stock;
	//vector<CardContainer> _containers;
	std::map<const CardContainerID, CardContainer*> _containers;
};

#endif