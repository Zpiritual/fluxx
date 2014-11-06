//undecided whether _players stores Simple player copies or references
//Changelog:
//==========
//2014-11-06
//Changed std::vector to std::map
#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H
#include "Player.h"
#include "PlayerID.h"
#include <vector>
#include <map>
class PlayerManager
{
public:
	PlayerManager(const std::vector<Player> players)
	{
		for(auto a: players)
			_players[a.getID()] = a;
	}

	PlayerManager()						= delete;
	PlayerManager(const PlayerManager&) = default;
	PlayerManager (PlayerManager&&) 	= default;

	PlayerManager& operator= (const PlayerManager&) = default;
	PlayerManager& operator= (PlayerManager&&) 		= default;

	~PlayerManager() = default;

	const Player 	getPlayer(const PlayerID pid) const	{	return _players.at(pid);	}
	void 			addPlayer(Player& p)				{	_players[p.getID()] = p;	}
private:
	std::map<const PlayerID, Player> _players;
};
#endif