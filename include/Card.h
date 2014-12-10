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
    Card(const CardID, const string, const string, const string, const string, const vector<Effect>);

	Card() 							= delete;
	Card(const Card&) 				= default;
	Card (Card&&) 					= default;

	Card& operator= (const Card&)	= default;
	Card& operator= (Card&&)		= default;

	~Card() 						= default;

	CardID 			getID() 			const;
    string        	getName()         const;
	string 			getType() 		const;
	string 			getSubtype() 		const;
	string 		 	getDescription() 	const;
	vector<Effect>  getEffects()		const;

private:
	const CardID _id;
    const string _name;
	const string _type;
	const string _subtype;
	const string _description;
	const vector<Effect> _effects;
};

#endif
