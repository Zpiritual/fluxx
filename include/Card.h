//Changelog:
//==========
#ifndef CARD_H
#define CARD_H

#include "CardID.h"
#include "Effect.h"
#include <vector>
#include <string>
using namespace std;

class Card
{
public:
	Card(const CardID id, const string type, const string subtype, const string description, const vector<Effect*> effects)
	: _id{id}, _type{type}, _subtype{subtype}, _description{description}, _effects{effects}
	{}

	Card() 							= delete;
	Card(const Card&) 				= delete;
	Card (Card&&) 					= delete;

	Card& operator= (const Card&)	= delete;
	Card& operator= (Card&&)		= delete;

	~Card() {
		for (auto i : _effects)
			delete i;
	}

	const CardID 		  getID() 			{ return _id; }
	const string 		  getType() 		{ return _type; }
	const string 		  getSubtype() 		{ return _subtype; }
	const string 		  getDescription() 	{ return _description; }
	const vector<Effect*> getEffects()		{ return _effects; }

private:
	const CardID _id;
	const string _type;
	const string _subtype;
	const string _description;
	const vector<Effect*> _effects;
};

#endif