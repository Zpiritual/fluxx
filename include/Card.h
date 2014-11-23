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

class Card
{
public:
	Card(const CardID id, const string type, const string subtype, const string description, const vector<Effect> effects);

	Card() 							= delete;
	Card(const Card&) 				= default;
	Card (Card&&) 					= default;

	Card& operator= (const Card&)	= default;
	Card& operator= (Card&&)		= default;

	~Card() 						= default;

	const CardID 		  getID() 			const;
	const string 		  getType() 		const;
	const string 		  getSubtype() 		const;
	const string 		  getDescription() 	const;
	const vector<Effect>  getEffects()		const;

private:
	const CardID _id;
	const string _type;
	const string _subtype;
	const string _description;
	const vector<Effect> _effects;
};

#endif