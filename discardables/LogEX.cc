static void game_to_log_init(string deck, string player_count, string player_names, string deck_after_deal)
{
	ofstream ofs("session.log");
	ofs << deck << "\n";
	ofs << player_count << "\n";
	ofs << player_names << "\n";
	ofs.close();
}
static void game_to_log_runtime(string player_name, string commands)
{
	ofstream ofs("session.log");
	ofs << player_name 	 << "\n";
	ofs << commands		 << "\n";
	ofs.close();
}

static void log_to_game_init()
{
	ifstream ifs("session.log");
	//====Reading stock=====//
 	{
 		vector<CardID> deckTmp;
 		string line;
 		ifs >> ws;
		getline(ifs, line);
		stringstream ss;(line);
 		int tmp;
		while(ss >> tmp)
		{
			deckTmp.push_back(CardID(tmp));
		}
		ccm->setStock(deckTmp);
 	}

	//====Reading hands=====//
 	{
 		int player_count;
 		ifs >> ws;
 		ifs >> player_count;
 		ifs >> ws;
		string line;
		getline(ifs,line);
		stringstream ss(line);
 		for(int i = 0 ; i < player_count; i++)
 		{
		string t;	
		int t1,t2,t3;
		ifs >> t >> t1 >> t2 >> t3;
 		ccm->moveCard(ContainerID("Stock"), ContainerID(t + "_hand"), t1));
		ccm->moveCard(ContainerID("Stock"), ContainerID(t + "_hand"), t2));
		ccm->moveCard(ContainerID("Stock"), ContainerID(t + "_hand"), t3));
 		}
 	}

 	//====Verifying stock===== DEBUG//
 	{
 		vector<CardID> deckTmp;
 		string line;
 		ifs >> ws;
 		getline(ifs, line);
 		stringstream ss(line);
 		int tmp;
 		while(ss >> tmp)
 		{
 			deckTmp.push_back(CardID(tmp));
 		}
 		ccm->verifyStock(deckTmp);
 	}
}
enum LogTags
{
	MOVE = "move",
	PLAY = "play",
	SWAP = "swap",
	ROT = "rotate"
};

static void log_to_game_runtime()
{
	ifstream ifs("session.log");
	ifs >> ws;
	string line;
	string cp;
	while(getline(ifs,line))
	{
		stringstream ss(line);
		string t;
		if(!(ss >> t))
		{
			nextPlayer();
			continue;
		}
		if(playerTurn(PlayerID(t)))
		{
			cp = t;
			continue;
		} 
		switch(t)
		{
			case MOVE:
			int t1;
			string t2,t3;
			ss >> t1 >> t2 >> t3;
			ccm->moveCard(t2, t3, t1);
			break;

			case PLAY:
			int t1;
			ss >> t1;
			playCard(PlayerID(cp), t1);
			break;

			case SWAP:
			string t1,t2;
			ccm->swap(ContainerID(t1), ContainerID(t2));
			break;

			case ROT:
			int t1;
			ifs >> t1;
			rm->setPlayOrder(t1));
			break;

			case default:
			cout << "Error reading game log !! " << endl;
			break;
		}
	}
}