//Changelog:
//==========
//2014-11-06
//Changed CardID* to CardID
//Changed ContainerID* to ContainerID
//2014-11-13
//Added const to _ID

#ifndef CARDCONTAINER_H
#define CARDCONTAINER_H
#include <vector>
#include "CardID.h"
#include "ContainerID.h"

class CardContainer
{
private:
	std::vector<CardID> _cards;
	const ContainerID _id;
public:
	CardContainer(std::vector<CardID> cards, const ContainerID id):_cards{cards}, _id{id}
	{}
	CardContainer(const ContainerID id): _id{id}
	{}

	CardContainer() 					= delete;
	CardContainer(const CardContainer&) = default;
	CardContainer(CardContainer&&) 		= delete;

	CardContainer& operator= (const CardContainer&) = default;
	CardContainer& operator= (CardContainer&&) 		= delete;

	~CardContainer() = default;

	void addCard(CardID);
	void removeCard(CardID);

	const int 					getSize() 	const;
	const std::vector<CardID> 	getCards() 	const ;
	const ContainerID 			getID() 	const;
};
#endif