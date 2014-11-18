#ifndef CARDCONTAINERMANAGER_H
#define CARDCONTAINERMANAGER_H
#include <"CardContainer.h">
#include <"Deck.h">
#include <"Stock.h">

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
	void drawCard(const ContainerID);
	void moveCard(const ContainerID, const ContainerID, const CardID);
	int getSize(const ContainerID) const;
	const vector<CardID> getCards(const ContainerID) const;

private:
	CardContainer* const getContainer(const ContainerID) const;

	Stock* _stock;
	//vector<CardContainer> _containers;
	map<ContainerID, CardContainer*> _containers;
};