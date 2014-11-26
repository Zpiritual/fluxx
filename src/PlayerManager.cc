#include "PlayerManager.h"
#include <stdexcept>

PlayerManager::PlayerManager(const std::vector<Player> players): _players{players}
{}

Player* PlayerManager::getPlayer(const PlayerID pid)	
{
	for(unsigned int i =0; i < _players.size(); i++)
	{
		if(_players.at(i).getID() == pid) return &_players.at(i);
	}

	throw std::logic_error("PlayerManager::getPlayer() - Felaktig PlayerID");
}

void PlayerManager::addPlayer(Player p)				
{
	_players.push_back(p);
}

Player* PlayerManager::getCurrentPlayer() 
{	
	return &_players.at(_current_player);	
}

const PlayerID PlayerManager::getCurrentPlayerID()
{
	return getCurrentPlayer()->getID();
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
	_players.at(_current_player).resetCardsPlayed();
	_current_player = (_current_player + 1) % _players.size();
}