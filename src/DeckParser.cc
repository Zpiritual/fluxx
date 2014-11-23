#include "DeckParser.h"
#include "Card.h"
#include <iostream>
Deck* DeckParser::deck_to_game(std::string filename)
{
	ifstream ifs{filename};
	string deck_name;
	int deck_size;
	string deck_description;

	string temp;
	ifs >> temp;
	ifs >> deck_name;

	ifs >> temp;
	ifs >> deck_size;

	ifs >> temp;
	getline(ifs, deck_description);
	vector<const Card*> cards;
	string line;
	for(int i = 0; i < deck_size; i++)
	{
		ifs >> ws;
		int id;
		string name;
		string type;
		string description;
		vector<Effect> effects;
		while(getline(ifs, line) && !line.empty())
		{	
			stringstream ss{line};
			string t;
			ss >> t;
			if(t == "CARD_ID")
			{
				ss >> id;
			}	
			else if(t == "CARD_NAME")
			{
				ss >> name;
			}
			else if(t == "CARD_TYPE")
			{
				ss >> type;
			}
			else if(t == "CARD_DESCRIPTION")
			{
				ss >> ws;
				getline(ss,description);
			}
			else if(t == "CARD_RULE")
			{
				//ss >> description;
				//cout << "Effect:" << effects.size() << endl;
			}
		}
		cout << "NEW CARD:" << endl;
		cout << "=========" << endl;
		cout << "ID: " << id << endl;
		cout << "NAME: " << name << endl;
		cout << "Type: " << type << endl;
		cout << "Description: " << description << endl;
		cout << "Effect:" << effects.size() << endl;
		cards.push_back(new Card(id, name, type, description, effects));
	}
	ifs.close();
	return new Deck(cards);
}