#ifndef STOCK_H
#define STOCK_H

#include <stack>
#include "CardID.h"
#include "CardContainerID.h"
#include "Deck.h"

class Stock
{
private:
	std::stack<CardID> _cards;
	const CardContainerID _id;

public:
	Stock(const CardContainerID id);
	Stock()							= delete;
	Stock(const Stock&)				= default;
	Stock(Stock&&)					= delete;

	Stock& operator= (const Stock&) = default;
	Stock& operator= (Stock&&) 		= delete;

	~Stock() = default;

	void 				push(const CardID id);
	CardID 				pop();
	bool 				empty() 	const;
	int 				getSize() 	const;
	std::stack<CardID>	getCards() 	const;
	CardContainerID 	getID() 	const;
	void 				shuffle();
};

#endif