#include "PlayerManager.h"
#include <stdexcept>
#include <iostream>
PlayerManager::PlayerManager(const int players)
{
	_players.push_back(PlayerID(PlayerIdentifier::Player1));
	_players.push_back(PlayerID(PlayerIdentifier::Player2));
	if (players > 2) {
		_players.push_back(PlayerID(PlayerIdentifier::Player3));
		if (players > 3) {
			_players.push_back(PlayerID(PlayerIdentifier::Player4));
			if (players > 4) {
				_players.push_back(PlayerID(PlayerIdentifier::Player5));
				if (players > 5) {
					_players.push_back(PlayerID(PlayerIdentifier::Player6));
				}
			}
		}
	}
}

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
	std::cout << _current_player << std::endl;
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
std::vector<Player> PlayerManager::getPlayers()
{
	return _players;
}

void PlayerManager::nextPlayer()
{
	_players.at(_current_player).resetCardsPlayed();
	_current_player = (_current_player + 1) % _players.size();
}