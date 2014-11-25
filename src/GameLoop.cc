#include "GameLoop.h"
#include "RuleManager.h"

void GameLoop::playCard(const PlayerID, const CardID);
void GameLoop::drawCards(const PlayerID, const int);

const int GameLoop::getDrawNO() const
{
	return _game_logic->getRM()->getDraw();
}

const int GameLoop::getPlayNO() const
{
	return _game_logic->getRM()->getPlay();
}

void GameLoop::sendLog(std::string);

const PlayerID	getCurrentPlayer() const
{
	return _game_logic->getRM()->getCurrentPlayerID();
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

	drawCards(getCurrentPlayer(), getDrawNO());
	
	checkTriggeredRules(RuleTrigger::POST_DRAW);

 	//spela kort
 	while (GameLogic->PlayerManager->played_cards < GameLogic->RuleManager->cards_to_play) // played_cards ligger i player.
 	{
 		GameLogic->playCard();
 		++played_cards;
 	}

}

void GameLoop::switchScreen();
void GameLoop::sendBoardState();
CardID GameLoop::requestInput();