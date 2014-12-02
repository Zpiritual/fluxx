#include "Card.h"
#include "Effect.h"

Card::Card(const CardID id, const string name, const string type, const string subtype, const string description, const vector<Effect> effects)
	:_id{id},
     _name{name},
	 _type{type},
	 _subtype{subtype},
	 _description{description},
	 _effects{effects}
	{}

CardID 		  	Card::getID() 			const	{ return _id; }
string          Card::getName()         const   { return _name; }
string 		  	Card::getType() 		const	{ return _type; }
string 		  	Card::getSubtype() 		const	{ return _subtype; }
string 		  	Card::getDescription() 	const	{ return _description; }
vector<Effect>  Card::getEffects()		const	{ return _effects; }
