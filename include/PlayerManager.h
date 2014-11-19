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
	PlayerManager(const std::vector<Player> players): _players{players}
	{}

	PlayerManager()						= delete;
	PlayerManager(const PlayerManager&) = default;
	PlayerManager (PlayerManager&&) 	= default;

	PlayerManager& operator= (const PlayerManager&) = default;
	PlayerManager& operator= (PlayerManager&&) 		= default;

	~PlayerManager() = default;

	const Player 	getPlayer(const PlayerID pid) const	
	{
		for(auto a: _players)
		{
			if(a.getID() == pid) return a;
		}
	}
	
	void 			addPlayer(Player p)				
	{
		_players.push_back(p);
	}

	const Player  getCurrentPlayer() const 
	{	
		return _players.at(_current_player);	
	}

	void 			setCurrentPlayer(const PlayerID pid)
	{	
		for(int i = 0; i < _players.size(); i++)
		{
			if(_players.at(i).getID() == pid) _current_player = i;
		}	
	}

	void 			nextPlayer()
	{
		_current_player = (_current_player + 1) % _players.size();
	}
private:
	std::vector<Player> _players;
	int  _current_player;
};
#endif