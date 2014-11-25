#include "GameLoop.h"
#include "RuleManager.h"

void GameLoop::playCard(const PlayerID, const CardID);

void GameLoop::drawCards(const PlayerID pid, const int draw_no);
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

void GameLoop::sendLog(std::string);

const PlayerID	getCurrentPlayerID() const
{
	return _game_logic->getRM()->getCurrentPlayerID();
}

const int getCardsPlayed() const
{
	_game_logic->getRM()->getCurrentPlayer()->getCardsPlayed();
}

void incrementCardsPlayed() const
{
	_game_logic->getRM()->getCurrentPlayer()->incrementCardsPlayed();
}

void GameLoop::nextPlayer()
{
	_game_logic->getRM()->nextPlayer();
}

SessionData	GameLoop::run()
{
	while (executePlayerTurn(getNextPlayer()) != GAME_OVER)
	{
		//switch screen osv.
		nextPlayer();
	}
}

const gameState GameLoop::executePlayerTurn(PlayerID)
{
	checkTriggeredRules(RuleTrigger::PRE_DRAW);

	drawCards(getCurrentPlayerID(), getDrawNO());
	
	checkTriggeredRules(RuleTrigger::POST_DRAW);

 	//spela kort
 	while (getPlayNO() < getCardsPlayed()) // played_cards ligger i player.
 	{
 		GameLogic->playCard(getCurrentPlayerID());
 		++played_cards;
 	}

}

void GameLoop::switchScreen();
void GameLoop::sendBoardState();
CardID GameLoop::requestInput();