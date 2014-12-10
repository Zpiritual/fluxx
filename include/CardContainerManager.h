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
#include <iostream>

class CardContainerManager : public Subject
{
public:
	CardContainerManager(const Deck* const);

	CardContainerManager() 											= delete;
	CardContainerManager(const CardContainerManager&) 				= delete;
	CardContainerManager(CardContainerManager&&) 					= delete;

	CardContainerManager& operator= (const CardContainerManager&)	= delete;
	CardContainerManager& operator= (CardContainerManager&&)		= delete;

	~CardContainerManager();

	void reshuffle();
	void drawCard(const CardContainerID);
	void moveCard(const CardContainerID, const CardContainerID, const CardID);
	void containerToStock(const CardContainerID);
	void moveCards(const CardContainerID, const CardContainerID);
	int getSize(const CardContainerID);
	std::vector<CardID> getCards(const CardContainerID);
	std::vector<CardContainer> getContainers() const;
    CardID getRandomCard(const CardContainerID);
	void unSuspendCard(const CardContainerID& ccid);
	void suspendCard(const CardContainerID& ccid, const CardID& cid);
	void swapCards(const CardContainerID, const CardContainerID);
	CardContainerID newTemp();
	CardContainerID getTemp() const;
	void deleteTemp();
	bool isEmptyTemp() const;

private:
	CardContainer* getContainer(const CardContainerID);
	Stock* _stock;
	std::map<const CardContainerID, CardContainer*> _containers;
    std::stack<CardID> _suspendedCards;
    std::stack<CardContainer*> _temps;
};

#endif
