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
	if(temp.empty())
	{
		cout << temp << endl;
		ifs.close();
		throw std::logic_error("No Deck Found @" + filename);
	}
	
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
		string type;
		string subType;
		string description;
		string effect;
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
			else if(t == "CARD_SUBTYPE")
			{
				ss >> subType;
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
			else if(t == "CARD_EFFECT")
			{
				ss >> ws;
				getline(ss,effect);
				effects.push_back(Effect{effect});
				//cout << "Effect: " << effect << "\t";
			}
		}
		
		//debug stuff:
		cout << "NEW CARD:" << endl;
		cout << "=========" << endl;
		cout << "ID: " << id << endl;
		cout << "TYPE: " << type << endl;
		cout << "SubType: " << subType << endl;
		cout << "Description: " << description << endl;
		cout << "Effect:" << effects.size() << endl;
		//TODO make sure it reads SubType
		cards.push_back(new Card(id, type, subType, description, effects));
	}
	if(cards.size() != deck_size)
	{
		cout << cards.size() << endl;
		cout << deck_size << endl;
		throw std::logic_error("Error in reading from: " +  filename);
	}

	ifs.close();
	return new Deck(cards);
}