#include "DeckParser.h"
#include "Card.h"
#include <iostream>

Deck* DeckParser::deck_to_game(std::string filename)
{
	ifstream ifs{filename};
	string deck_name;
	unsigned deck_size;
	string deck_description;

	string temp;
	ifs >> temp;
	if(temp.empty())
	{
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
	
	for(unsigned i = 0; i < deck_size; i++)
	{
		ifs >> ws;
		int id;
        string name = "";
		string type;
		string subtype;
		string description;
		string effect;
		vector<Effect> effects;
		
		while(getline(ifs, line) && !line.empty())
		{	
			stringstream ss{line};
			string t;
			ss >> t;
			if(t.compare("CARD_ID") == 0)
			{
				ss >> id;
            }
            else if(t.compare("CARD_NAME") == 0)
            {
               getline(ss,name);
            }
            else if(t.compare("CARD_TYPE") == 0)
			{
				ss >> type;
			}
            else if(t.compare("CARD_SUBTYPE") == 0)
			{
				ss >> subtype;
			}
            else if(t.compare("CARD_DESCRIPTION") == 0)
			{
				ss >> ws;
				getline(ss,description);
			}
            else if(t.compare( "CARD_EFFECT") == 0)
			{
				getline(ss,effect);
				Effect e{effect};
				effects.push_back(e);
			}
		}
		
	//debug stuff:
		cerr << "NEW CARD:" << endl;
		cerr << "=========" << endl;
		cerr << "ID: " << id << endl;
    	cerr << "NAME: " << name << endl;
		cerr << "TYPE: " << type << endl;
		cerr << "SubType: " << subtype << endl;
		cerr << "Description: " << description << endl;
		cerr << "Effect:" << effects.size() << endl;
        cards.push_back(new Card(id, name, type, subtype, description, effects));
	}

	if(cards.size() != deck_size)
	{
        cerr << "Mismatch: Deck size does not correspond to number of cards in file.\nDeck size: "
             << deck_size << "\nNumber of cards: "<< cards.size() << endl;
		throw std::logic_error("Invalid deck definition file: " +  filename);
	}

	ifs.close();
	return new Deck(cards);
}
