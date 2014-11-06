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
}