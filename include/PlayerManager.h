//undecided whether _players stores Simple player copies or references
//Changelog:
//==========
//2014-11-06
//Changed std::vector to std::map
//2014-11-18
//Added function setCurrentPlayer(PlayerID) 
//Added function getCurrentPlayer()
//Added member	 currentPlayer
//Added function nextPlayer;
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
	const PlayerID getCurrentPlayer() const {	return _current_player;	}
	void setCurrentPlayer(const PlayerID pid){	_current_player = pid;	}
	void nextPlayer();
private:
	std::map<const PlayerID, Player> _players;
	PlayerID _current_player;
};
#endif