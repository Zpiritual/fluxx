//Changelog:
//==========
//2014-11-12
//Added const to ContainerID
//2014-11-14
//Removed const from stack and vector given <const T> not allowed
//2014--11-20
//moved constructor and destructor to .cc
//added forward declaration
#ifndef STOCK_H
#define STOCK_H

#include <random>
#include <stack>
#include "CardID.h"
#include "CardContainerID.h"
#include "Deck.h"
class Deck;
class Stock
{
private:
	std::stack<CardID> _cards;
	const CardContainerID _id;
public:
	Stock(const Deck  * deck , const CardContainerID id);

	Stock(const CardContainerID id);
	Stock() 					= delete;
	Stock(const Stock&) = default;
	Stock(Stock&&) 		= delete;

	Stock& operator= (const Stock&) = default;
	Stock& operator= (Stock&&) 		= delete;

	~Stock() = default;

	void 							push(const CardID id);
	const CardID 					pop();
	const bool 						empty() 	const;
	const int 						getSize() 	const;
	const std::stack<CardID> 		getCards() 	const;
	const CardContainerID 			getID() 	const;
	void 							shuffle();
};
#endif