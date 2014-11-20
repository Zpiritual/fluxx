#include "Card.h"

Card::Card(const CardID id, const string type, const string subtype, const string description, const vector<Effect*> effects)
	: _id{id}, _type{type}, _subtype{subtype}, _description{description}, _effects{effects}
	{}
Card::~Card()
 {
		for (Effect* i : _effects)
			delete i;
}