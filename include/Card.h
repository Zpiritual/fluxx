//Changelog:
//==========
//2014-11-06
//Added const to getters
//2014-11-14
//Changed copy and move constructor/operators to default
#ifndef CARD_H
#define CARD_H
#include "CardID.h"
#include "Effect.h"
#include <vector>
#include <string>
using namespace std;
class Effect;
class Card
{
public:
Card(const CardID id, const string type, const string subtype, const string description, const vector<Effect*> effects);

	Card() 							= delete;
	Card(const Card&) 				= default;
	Card (Card&&) 					= default;

	Card& operator= (const Card&)	= default;
	Card& operator= (Card&&)		= default;

	~Card();

	const CardID 		  getID() 			const	{ return _id; }
	const string 		  getType() 		const	{ return _type; }
	const string 		  getSubtype() 		const	{ return _subtype; }
	const string 		  getDescription() 	const	{ return _description; }
	const vector<Effect*> getEffects()		const	{ return _effects; }

private:
	const CardID _id;
	const string _type;
	const string _subtype;
	const string _description;
	const vector<Effect*> _effects;
};

#endif