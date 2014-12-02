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
#include <stack>
#include "Subject.h"

class CardContainerManager:public Subject {
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
	void clearContainer(const CardContainerID);
	int getSize(const CardContainerID);
	std::vector<CardID> getCards(const CardContainerID);
	std::vector<CardContainer> getContainers() const;
    CardID getRandomCard(const CardContainerID);
	void unSuspendCard(const CardContainerID& ccid);
	void suspendCard(const CardContainerID& ccid, const CardID& cid);

private:
	CardContainer* getContainer(const CardContainerID);
	Stock* _stock;
	std::map<const CardContainerID, CardContainer*> _containers;
    std::stack<CardID> _suspendedCards;
};

#endif
