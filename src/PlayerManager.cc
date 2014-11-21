#include "PlayerManager.h"
	PlayerManager::PlayerManager(const std::vector<Player> players): _players{players}
	{}
const Player PlayerManager::getPlayer(const PlayerID pid) const	
	{
		for(auto a: _players)
		{
			if(a.getID() == pid) return a;
		}
	}
	
	void PlayerManager::addPlayer(Player p)				
	{
		_players.push_back(p);
	}

	const Player  PlayerManager::getCurrentPlayer() const 
	{	
		return _players.at(_current_player);	
	}

	void PlayerManager::setCurrentPlayer(const PlayerID pid)
	{	
		for(unsigned int i = 0; i < _players.size(); i++)
		{
			if(_players.at(i).getID() == pid) _current_player = i;
		}	
	}

	void PlayerManager::nextPlayer()
	{
		_current_player = (_current_player + 1) % _players.size();
	}