//Changelog:
//==========
//2014-11-06
//Included more tests and added return 0
#include "Card.h"
#include <cassert>
#include <iostream>

int main() {
vector<Effect*> e1;
e1.push_back(new Effect);
Card c1(CardID(000), "type1", "subtype1", "description1", e1);

cout << "\nCardID: " 	  << c1.getID().val
	 << "\nType: " 		  << c1.getType()
	 << "\nSubtype: "	  << c1.getSubtype()
	 << "\nDescription: " << c1.getDescription();

Card c2(CardID(001), "type2", "subtype1", "description2", e1);
Card c3(CardID(002), "type2", "subtype1", "description2", e1);
Card c4(CardID(003), "type2", "subtype1", "description2", e1);
Card c5(CardID(000), "type2", "subtype1", "description2", e1);
	assert(c1.getID() != c2.getID());
	assert(c2.getID() != c3.getID());
	assert(!(c3.getID() == c4.getID()));
	assert(c1.getID() == c5.getID());
	cout << "\nSanty check: IDs equ/neq works \n";
	return 0;
}