#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "Player.h"
#include "PlayerID.h"
#include <vector>
#include <map>

class PlayerManager
{
public:
	PlayerManager(const int players);

	PlayerManager()						= delete;
	PlayerManager(const PlayerManager&) = default;
	PlayerManager (PlayerManager&&) 	= default;

	PlayerManager& operator= (const PlayerManager&) = default;
	PlayerManager& operator= (PlayerManager&&) 		= default;

	~PlayerManager() = default;

	Player*		 	getPlayer(const PlayerID pid);
	void 			addPlayer(Player p);
	
	Player*		  			 getCurrentPlayer();
	PlayerID				 getCurrentPlayerID();
	PlayerID				 getNextPlayerID(Direction direction);
	std::vector<Player>		 getPlayers() const;
	std::vector<PlayerStats> getPlayerStats() const;

    void 			nextPlayer(Direction);
    void			repeatTurn();
    PlayerID		getWinningPlayer();
    void			setWinningPlayer(PlayerID);

private:
	std::vector<Player> _players;
	int  _current_player = 0;
	bool _repeat_turn{false};
	PlayerID _winning_player;
};

#endif
