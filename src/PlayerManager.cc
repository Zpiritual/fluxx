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
	return &_players.at(_current_player);	
}

PlayerID PlayerManager::getCurrentPlayerID()
{
	return getCurrentPlayer()->getID();
}

PlayerID PlayerManager::getNextPlayerID(Direction direction)
{
	if(!_repeat_turn)
	{
		if (direction == Direction::CLOCKWISE)
	    {
            return getPlayers().at((_current_player + 1) % _players.size()).getID();
	    }
	    else if (direction == Direction::COUNTERCLOCKWISE)
	    {
            const int next_player = (_current_player - 1);

	        if (next_player < 0)
	        {
                return getPlayers().at(_players.size()-1).getID();
	        }
            else
            {
                return getPlayers().at(next_player).getID();
            }
	    }	
	}
    return getCurrentPlayerID();
}

std::vector<Player> PlayerManager::getPlayers() const
{
	return _players;
}

std::vector<PlayerStats> PlayerManager::getPlayerStats() const
{
    std::vector<PlayerStats> stats;

	for(Player p : getPlayers())
	{
		stats.push_back(p.makeStats());
	}
	return stats;
}

void PlayerManager::nextPlayer(Direction direction)
{
    Player* player(&_players.at(_current_player));

	if ( player->getConsecutivePlays() > player->getMaxConsecutivePlays() )
	{
		player->setMaxConsecutivePlays(player->getConsecutivePlays());
	}

	player->resetCardsPlayed();
	player->resetCardsDrawn();

	if ( getCurrentPlayerID() != getNextPlayerID(direction) )
	{
		player->resetConsecutivePlays();	
	}
	
	if(!_repeat_turn)
	{
		if (direction == Direction::CLOCKWISE)
	    {
	        _current_player = (_current_player + 1) % _players.size();
	    }
	    else if (direction == Direction::COUNTERCLOCKWISE)
	    {
	        _current_player = (_current_player - 1);

	        if (_current_player < 0)
	        {
	            _current_player = int(_players.size()-1);
	        }
	    }	
	}
	else
	{
		_repeat_turn = false;
	}
}

void PlayerManager::repeatTurn()
{
	if(_repeat_turn)
	{
        std::cerr << "PlayerManager::repeatTurn() - Invalid instruction. Current turn already marked for repeat." << std::endl;
	}
	else
	{
		_repeat_turn = true;
	}
}

PlayerID PlayerManager::getWinningPlayer()
{
	return _winning_player;
}

void PlayerManager::setWinningPlayer(PlayerID winner)
{
	_winning_player = winner;
}
