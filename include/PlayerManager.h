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
	PlayerManager(const std::vector<Player> players);

	PlayerManager()						= delete;
	PlayerManager(const PlayerManager&) = default;
	PlayerManager (PlayerManager&&) 	= default;

	PlayerManager& operator= (const PlayerManager&) = default;
	PlayerManager& operator= (PlayerManager&&) 		= default;

	~PlayerManager() = default;

	const Player 	getPlayer(const PlayerID pid) const;
	void 			addPlayer(Player p);
	const Player  	getCurrentPlayer() const;
	void 			setCurrentPlayer(const PlayerID pid);
	void 			nextPlayer();
private:
	std::vector<Player> _players;
	int  _current_player;
};
#endif