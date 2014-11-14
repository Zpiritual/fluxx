//Changelog:
//==========
//2014-11-12
//Added const to ContainerID
//
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
	Stock(const Deck* deck const, const ContainerID id):_cards{deck->}, _id{id}
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

	void shuffle()
	{
		std::vector<CardID> tmp;
		while(!_cards.empty())
		{
			tmp.push_back(pop());
		}
 		std::default_random_engine generator;
  
		while(!tmp.empty())
		{
			std::uniform_int_distribution<int> distribution(0,tmp.size()-1);
			unsigned int i = distribution(generator);
			push(tmp.at(i));
			tmp.erase(tmp.begin() + i);
		}
	}

	const int 					getSize() 	const;
	const std::stack<CardID> 	getCards() 	const ;
	const ContainerID 			getID() 	const;
};
#endif