#include "PlayerManager.h"
	PlayerManager::PlayerManager(const std::vector<Player> players): _players{players}
	{}
const Player Player::getPlayer(const PlayerID pid) const	
	{
		for(auto a: _players)
		{
			if(a.getID() == pid) return a;
		}
	}
	
	void Player::addPlayer(Player p)				
	{
		_players.push_back(p);
	}

	const Player  Player::getCurrentPlayer() const 
	{	
		return _players.at(_current_player);	
	}

	void Player::setCurrentPlayer(const PlayerID pid)
	{	
		for(int i = 0; i < _players.size(); i++)
		{
			if(_players.at(i).getID() == pid) _current_player = i;
		}	
	}

	void Player::nextPlayer()
	{
		_current_player = (_current_player + 1) % _players.size();
	}