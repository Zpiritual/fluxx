#ifndef CARDCONTAINERMANAGER_H
#define CARDCONTAINERMANAGER_H

#include "CardContainerID.h"
#include "Deck.h"
#include "Stock.h"

class CardContainerManager {
public:
	CardContainerManager(const Deck* const deck);
	// Konstruktorn skall initiera både stock-objektet och vektorn med cardcontainers.

	CardContainerManager() 											= delete;
	CardContainerManager(const CardContainerManager&) 				= delete;
	CardContainerManager(CardContainerManager&&) 					= delete;

	CardContainerManager& operator= (const CardContainerManager&)	= delete;
	CardContainerManager& operator= (CardContainerManager&&)		= delete;

	~CardContainerManager() 										= default;

	//const CardID popDeck(); 
	// Kan nog tas bort helt, verkar överflödig.
	void reshuffle();
	void drawCard(const CardContainerID);
	void moveCard(const CardContainerID, const CardContainerID, const CardID);
	int getSize(const ContainerID) const;
	const vector<CardID> getCards(const CardContainerID) const;

private:
	const CardContainer* const getContainer(const CardContainerID) const;

	Stock _stock;
	//vector<CardContainer> _containers;
	map<CardContainerID, CardContainer> _containers;
};

#endif