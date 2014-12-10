#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include "CardID.h"
#include <map>
#include <vector>

class Deck
{
public:
	Deck(const std::vector< const Card* > &cards);

	Deck() = delete;
	Deck(const Deck&) = default;
	Deck (Deck&&) = default;

	Deck& operator= (const Deck&) = default;
	Deck& operator= (Deck&&) = default;

	~Deck();

	int					getSize()				 const;
	std::vector<CardID> getCardIDList()			 const;
	const Card*			getCard(const CardID id) const;

private:
	std::map<const CardID, const Card* > _cards;
};

#endif
