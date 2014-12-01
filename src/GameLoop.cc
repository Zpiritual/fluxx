#include "GameLoop.h"
#include "enums.h"
#include <iostream>

GameLoop::GameLoop(const Deck * deck, const int players)
{
	std::cout << "\nBefore assignment to _game_logic" << std::endl;
	_game_logic = new GameLogic(deck, players);
	std::cout << "\nAfter assignment to _game_logic" << std::endl;
}

GameLoop::~GameLoop()
{
	std::cout << "\nBefore deletion of _game_logic" << std::endl;
	delete _game_logic;
	std::cout << "\nBefore deletion of _game_logic" << std::endl;
}

// void GameLoop::playCard(const PlayerID, const CardID)
// {

// }

void GameLoop::drawCards(const PlayerID pid, const int draw_no)
{
	for (int i = 0; i < draw_no; ++i)
	{
		_game_logic->drawCard(pid);
	}
}

const int GameLoop::getDrawNO() const
{
	return _game_logic->getRM()->getDraw();
}

const int GameLoop::getPlayNO() const
{
	return _game_logic->getRM()->getPlay();
}

// const PlayerID GameLoop::getNextPlayerID()
// {
// 	return _game_logic->getPM()
// }

void GameLoop::sendLog(std::string)
{

}

const PlayerID	GameLoop::getCurrentPlayerID() const
{
	return _game_logic->getPM()->getCurrentPlayerID();
}

const int GameLoop::getCardsPlayed() const
{
	_game_logic->getPM()->getCurrentPlayer()->getCardsPlayed();
}

void GameLoop::incrementCardsPlayed()
{
	_game_logic->getPM()->getCurrentPlayer()->incrementCardsPlayed();
}

void GameLoop::nextPlayer()
{
	_game_logic->getPM()->nextPlayer();
}

SessionData	GameLoop::run()
{
	while (executePlayerTurn(getCurrentPlayerID()) != GameState::GAME_OVER)
	{
		//switch screen osv.
		nextPlayer();
	}
}

const GameState GameLoop::executePlayerTurn(PlayerID pid)
{
	std::cout << pid.getString() << std::endl;
	checkTriggeredRules(RuleTrigger::PRE_DRAW);

	drawCards(getCurrentPlayerID(), getDrawNO());
	
	checkTriggeredRules(RuleTrigger::POST_DRAW);

	checkTriggeredRules(RuleTrigger::PRE_PLAY);
	//std::cout <<"Cards played: " << getCardsPlayed() << std::endl;
 	//spela kort
 	while (getCardsPlayed() < getPlayNO()) // played_cards ligger i player.
 	{
 		std::cout << "Cards to play: " << getPlayNO() << " Cards Played: " << getCardsPlayed() << endl;
 		std::cout << "Play cards" + pid.getString() << std::endl;
 		_game_logic->playCard(getCurrentPlayerID());
 		_game_logic->getPM()->getCurrentPlayer()->incrementCardsPlayed();
 	}
 	std::cout << "END OF TURN\n\n" << std::endl;

}

void GameLoop::checkTriggeredRules(RuleTrigger rule)
{
//	_game_logic->checkRules(rule);
	//std::cout << "Check rules" << std::endl;
}

void GameLoop::switchScreen()
{

}

void GameLoop::sendBoardState()
{

}

CardID GameLoop::requestInput()
{

}
