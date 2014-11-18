static void deck_to_game_init()
{
	ifstream ifs{"deck.fluxx"};
	string deck_name;
	int deck_size;
	string deck_description;

	string temp;
	ifs >> temp;
	ifs >> temp;
	deck_name = temp;

	ifs >> temp;
	ifs >> temp;
	deck_size = temp;

	ifs >> temp;
	ifs >> temp;
	deck_description = temp;
	ifs.close();
}
enum DeckTags
{
	ID = "CARD_ID",
	NAME = "CARD_NAME",
	TYPE = "CARD_TYPE",
	DESCRIPTION = "CARD_DESCRIPTION",
	RULE = "CARD_RULE"
	NEW = "";
}
static void deck_to_game_runtime()
{
	ifstream ifs{"deck.fluxx"};
	ifs >> ws;
	vector<Card*> cards;
	string line;

			int id;
		string name;
		CardType type;
		string description;
		vector<Effect> effects;
	while(getline(ifs, line))
	{
		stringstream ss{line};
		string t;
		ss >> t;
		switch(t)
		{
			case ID:
			break;
			case NAME:
			break;
			case TYPE:
			break;
			case DESCRIPTION:
			break;
			case RULE:
			break;
		}
	}
}
