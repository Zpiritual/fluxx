//Changelog:
//==========
//2014-11-12
//Added const to ContainerID
//2014-11-14
//Removed const from stack and vector given <const T> not allowed
#ifndef STOCK_H
#define STOCK_H
#include <random>
#include <stack>
#include "CardID.h"
#include "ContainerID.h"
#include "Deck.h"

class Stock
{
private:
	std::stack<CardID> _cards;
	const ContainerID _id;
public:
	Stock(const Deck  * deck , const ContainerID id):_id{id}
	{
		for(auto i: deck->getCardIDList())
		{
			push(i);
		}
	}

	Stock(const ContainerID id): _id{id}
	{}

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
	const std::stack<const CardID> 	getCards() 	const;
	const ContainerID 				getID() 	const;
};
#endif