#include "GameLoop.h"
#include "enums.h"

GameLoop::GameLoop(const Deck * deck, const int players)
	: _game_logic{new GameLogic(deck, players)}
{}

void GameLoop::playCard(const PlayerID, const CardID)
{

}

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

const PlayerID GameLoop::getNextPlayerID()
{
	
}

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
	while (executePlayerTurn(getNextPlayerID()) != GameState::GAME_OVER)
	{
		//switch screen osv.
		nextPlayer();
	}
}

const GameState GameLoop::executePlayerTurn(PlayerID)
{
	checkTriggeredRules(RuleTrigger::PRE_DRAW);

	drawCards(getCurrentPlayerID(), getDrawNO());
	
	checkTriggeredRules(RuleTrigger::POST_DRAW);

	checkTriggeredRules(RuleTrigger::PRE_PLAY);
	
 	//spela kort
 	while (getPlayNO() < getCardsPlayed()) // played_cards ligger i player.
 	{
 		_game_logic->playCard(getCurrentPlayerID());
 		_game_logic->getPM()->getCurrentPlayer()->incrementCardsPlayed();
 	}

}

void GameLoop::checkTriggeredRules(RuleTrigger rule)
{
//	_game_logic->checkRules(rule);
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
