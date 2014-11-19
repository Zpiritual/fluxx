//Changelog:
//==========
//2014-11-06
//Changed CardID* to CardID
//Changed ContainerID* to ContainerID
//2014-11-13
//Added const to _ID
//Removed CardContainer(vector, id) constructor
//2014-11-18
//Changed move constructor and operator to default

#ifndef CARDCONTAINER_H
#define CARDCONTAINER_H
#include <vector>
#include "CardID.h"
#include "CardContainerID.h"

class CardContainer
{
private:
	std::vector<CardID> _cards;
	const CardContainerID _id;
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

	const int 					getSize() 	const;
	const std::vector<CardID> 	getCards() 	const ;
	const CardContainerID 		getID() 	const;
};
#endif