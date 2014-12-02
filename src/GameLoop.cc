#include "GameLoop.h"
#include "enums.h"
#include <iostream>

GameLoop::GameLoop(Gui * gui, const Deck * deck, const int players)
{
	std::cerr << "\nBefore assignment to _game_logic" << std::endl;
    _game_logic = new GameLogic(gui, deck, players);
	std::cerr << "\nAfter assignment to _game_logic" << std::endl;
}

GameLoop::~GameLoop()
{
	std::cerr << "\nBefore deletion of _game_logic" << std::endl;
	delete _game_logic;
	std::cerr << "\nBefore deletion of _game_logic" << std::endl;
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
	std::cerr << "GameLoop::nextPlayer() - Before \"_game_logic->switchPlayer();\"" << endl;
	_game_logic->switchPlayer();
	std::cerr << "GameLoop::nextPlayer() - Before \"_game_logic->getPM()->nextPlayer(_game_logic->getRM()->getPlayOrder());\"" << endl;
	_game_logic->getPM()->nextPlayer(_game_logic->getRM()->getPlayOrder());
}

SessionData	GameLoop::run()
{
	_game_logic->getCCM()->reshuffle();
	while (executePlayerTurn(getCurrentPlayerID()) != GameState::GAME_OVER)
	{
		//switch screen osv.
		nextPlayer();
	}
}

const GameState GameLoop::executePlayerTurn(PlayerID pid)
{
	std::cerr <<"NEW TURN: "<< pid.getString() << std::endl;
	std::cerr <<"==========================" << std::endl;
	checkTriggeredRules(RuleTrigger::PRE_DRAW);

	drawCards(getCurrentPlayerID(), getDrawNO());
	
	checkTriggeredRules(RuleTrigger::POST_DRAW);

	checkTriggeredRules(RuleTrigger::PRE_PLAY);
	
 	while (getCardsPlayed() < getPlayNO() && _game_logic->getCCM()->getSize(getCurrentPlayerID().getString() + "_hand") != 0) // played_cards ligger i player.
 	{
 		std::cerr << "Cards to play: " << getPlayNO() << ", Cards Played: " << getCardsPlayed() << endl;
 		std::cerr << "Cards to Draw: " << getDrawNO() << ", Cards Drawn: " << _game_logic->getPM()->getCurrentPlayer()->getCardsDrawn() << endl;

 		_game_logic->playCard(getCurrentPlayerID());
 		_game_logic->getPM()->getCurrentPlayer()->incrementCardsPlayed();

 	}
 	std::cerr << "END OF TURN\n\n" << std::endl;
}

void GameLoop::checkTriggeredRules(RuleTrigger rule)
{
	_game_logic->checkRules(rule);
}
