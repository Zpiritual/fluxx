//Athor Martin
//============
//Default constructor deleted because it cant set the _id field any other way.
//Allows copy but not moving because a CardContainer will always be present att same memory addr 
//but allowd clones for BoardState.
#ifndef CARDCONTAINER_H
#define CARDCONTAINER_H
#include <vector>
#include "CardID.h"
#include "ContainerID.h"
class CardContainer
{
private:
	std::vector<CardID*> _cards;
	ContainerID* _id;
public:
	CardContainer(std::vector<CardID*> cards, ContainerID* id):_cards{cards}, _id{id}
	{}
	CardContainer(ContainerID* id): _id{id}
	{}

	//Default and Move forbidden
	CardContainer() = delete;
	CardContainer(const CardContainer&) = default;
	CardContainer(CardContainer&&) = delete;

	CardContainer& operator= (const CardContainer&) = default;
	CardContainer& operator= (CardContainer&&) = delete;

	//Default Destructor
	~CardContainer() = default;

	//public Modifiers
	void addCard(CardID*);
	void removeCard(CardID*);

	//public Capacity
	int getSize();
	std::vector<CardID*> getCards();
	ContainerID* getID();
};
#endif