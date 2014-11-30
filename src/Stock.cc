#include "Stock.h"
#include <stdexcept>
#include <ctime>
Stock::Stock(const CardContainerID id): _id{id}
{}

const int Stock::getSize() 	const
{
	return _cards.size();
}

const std::stack<CardID> 	Stock::getCards() 	const
{
	return _cards;
}

const CardContainerID 	Stock::getID() 	const
{
	return _id;
}

const CardID Stock::pop()
{
	if (_cards.empty())
	{
		throw std::logic_error("const CardID Stock::pop() - Tom kortlek!");
	}
	const CardID tmp = _cards.top();
	_cards.pop();
	return tmp;
}

void Stock::push(const CardID id)
{
	_cards.push(id);
}

const bool Stock::empty() 	const
{
	return _cards.empty();
}

void Stock::shuffle()
{
	std::vector<CardID> tmp;
	while(!_cards.empty())
	{
		tmp.push_back(pop());
	}
	int i = time(0);
    std::mt19937 gen(i);
	while(!tmp.empty())
	{
		std::uniform_int_distribution<int> distribution(0,tmp.size()-1);
		unsigned int i = distribution(gen);
		push(tmp.at(i));
		tmp.erase(tmp.begin() + i);
	}
}
