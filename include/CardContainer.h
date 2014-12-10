#ifndef CARDCONTAINER_H
#define CARDCONTAINER_H

#include <vector>
#include "CardID.h"
#include "CardContainerID.h"
#include <iostream>

class CardContainer
{
public:
	CardContainer(const CardContainerID id): _id{id}
	{}

	CardContainer() 					= delete;
	CardContainer(const CardContainer&) = default;
	CardContainer(CardContainer&&) 		= default;

	CardContainer& operator= (const CardContainer&) = default;
	CardContainer& operator= (CardContainer&&) 		= default;

    ~CardContainer() = default;

	void addCard(const CardID);
	void removeCard(const CardID);
	CardID getRandomCard() const;

	int 					getSize() 	const;
	std::vector<CardID> 	getCards() 	const ;
	CardContainerID 		getID() 	const;

private:
	std::vector<CardID> _cards;
	const CardContainerID _id;
};

#endif
