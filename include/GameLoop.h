//Changelog
//=========
//2014-11-26
//CHanged getNextPlayer to getNextPlayerID
//Changed executePlayerTurn return value from bool to GameState
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
#include "gui.h"
#include <vector>
#include <string>

class GameLoop
{
public:
    GameLoop(Gui * gui, const Deck * deck, const int players);

	GameLoop()							  = delete;
	GameLoop(const GameLoop&)			  = default;
	GameLoop (GameLoop&&)				  = default;

	GameLoop& operator= (const GameLoop&) = default;
	GameLoop& operator= (GameLoop&&) 	  = default;

	~GameLoop();
	
	// void			playCard(const PlayerID, const CardID);
	void 			drawCards(const PlayerID, const int);
	void 			nextPlayer();
	
	//const PlayerID	getNextPlayerID();
	GameState	executePlayerTurn(PlayerID);
	PlayerID	getCurrentPlayerID() const;
	int 		getDrawNO() const;
	int 		getPlayNO() const;
	int 		getCardsPlayed() const;
	
	void	 		incrementCardsPlayed();
	void 			sendLog(std::string);
	void			checkTriggeredRules(RuleTrigger);
	SessionData		run();


private:
	GameLogic * _game_logic = nullptr;
	//void	switchScreen();
	//void 	sendBoardState();
	//CardID 	requestInput();
};

#endif
