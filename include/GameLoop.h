#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "Deck.h"
#include "Player.h"
#include "GameLogic.h"
#include "PlayerID.h"
#include "CardID.h"
#include "RuleManager.h"
#include "SessionData.h"
#include "enums.h"
#include <vector>
#include <string>

class GameLoop
{
public:
	//QT referece adding later
	GameLoop(const Deck * deck, const std::vector<PlayerID> players);
	GameLoop()					= delete;
	GameLoop(const GameLoop&) = default;
	GameLoop (GameLoop&&) 	= default;

	GameLoop& operator= (const GameLoop&) = default;
	GameLoop& operator= (GameLoop&&) 		= default;

	~GameLoop();
	void			playCard(const PlayerID, const CardID);
	void 			drawCards(const PlayerID, const int);
	const bool		executePlayerTurn(PlayerID);
	const PlayerID	getCurrentPlayerID() const;
	const int 		getDrawNO() const;
	const int 		getPlayNO() const;
	const int 		getCardsPlayed() const;
	void	 		incrementCardsPlayed() const;
	void 			sendLog(std::string);
	void			checkTriggeredRules(TriggeredRule) const;
	SessionData		run();

private:
	GameLogic * _game_logic;
	void	switchScreen();
	void 	sendBoardState();
	CardID 	requestInput();
};

#endif