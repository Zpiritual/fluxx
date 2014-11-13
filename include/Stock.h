//Changelog:
//==========
//2014-11-12
//Added const to ContainerID
//
#ifndef STOCK_H
#define STOCK_H
#include <stack>
#include "CardID.h"
#include "ContainerID.h"
class Stock
{
private:
	std::stack<CardID> _cards;
	const ContainerID _id;
public:
	Stock(std::stack<CardID> cards, const ContainerID id):_cards{cards}, _id{id}
	{}
	Stock(const ContainerID id): _id{id}
	{}

	Stock() 					= delete;
	Stock(const Stock&) = default;
	Stock(Stock&&) 		= delete;

	Stock& operator= (const Stock&) = default;
	Stock& operator= (Stock&&) 		= delete;

	~Stock() = default;

	const CardID pop()
	{
		const CardID tmp = _cards.top();
		_cards.pop();
		return tmp;
	}

	void push(const CardID &id)
	{
		_cards.push(id);
	}

	const int 					getSize() 	const;
	const std::stack<CardID> 	getCards() 	const ;
	const ContainerID 			getID() 	const;
};
#endif