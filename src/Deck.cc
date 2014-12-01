#include "Deck.h"

Deck::Deck(const std::vector< const Card* > &cards)
{
	for(auto a: cards)
	{
		_cards.insert(std::pair<const CardID, const Card * >(a->getID(), a));
	}
}

Deck::~Deck()
{
	for(auto c: _cards)
		delete c.second;
}

const std::vector<CardID> Deck::getCardIDList() const 
{
	std::vector<CardID> v;
	for(auto it=_cards.begin(); it != _cards.end(); ++it)
	{
		v.push_back(it->first);
	}
	return v;
}

const Card* const Deck::getCard(const CardID id) const
{
	try
	{
		return _cards.at(id);
	}
	catch(...)
	{
		return nullptr;
	}
}

const int Deck::getSize() const 
{
	return _cards.size();
}