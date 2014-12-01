//Changelog:
//==========
//2014-11-06
//Included more tests and added return 0
#include "Card.h"
#include "Effect.h"
#include <cassert>
#include <iostream>

int main()
{
	vector<Effect> e1;
	e1.push_back(Effect{"test string"});
	Card c1(CardID(001), "name1", "type1", "subtype1", "description1", e1);

	cout << "CardID: " 	  << c1.getID().val
		 << "\nType: " 		  << c1.getType()
		 << "\nSubtype: "	  << c1.getSubtype()
		 << "\nDescription: " << c1.getDescription();

	Card c2(CardID(002), "name2", "type2", "subtype3", "description2", e1);
	Card c3(CardID(003), "name3", "type3", "subtype4", "description3", e1);
	Card c4(CardID(004), "name4", "type4", "subtype4", "description4", e1);

	Card c5(CardID(001), "name1", "type1", "subtype1", "description1", e1);

	//Make sure the equality operators function.
	assert(c1.getID() != c2.getID());
	assert(c2.getID() != c3.getID());
	assert(!(c3.getID() == c4.getID()));
	assert(c1.getID() == c5.getID());

	cout << "\nSanity check: IDs equ/neq works \n";
	
	return 0;
}