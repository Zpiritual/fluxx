#include "GameLoop.h"
#include "enums.h"
#include <iostream>
#include <string>
#include <limits>
#include <chrono>

GameLoop::GameLoop(Gui * gui, const Deck * deck, const int players)
{
    _game_logic = new GameLogic(gui, deck, players);
}

GameLoop::~GameLoop()
{
	delete _game_logic;
	_game_logic = nullptr;
}

void GameLoop::drawCards(const PlayerID pid, const int draw_no)
{
	for (int i = 0; i < draw_no; ++i)
	{
		_game_logic->drawCard(pid);
	}
}

int GameLoop::getDrawNO() const
{
	return _game_logic->getRM()->getDraw();
}

int GameLoop::getPlayNO() const
{
	const int play_rule = _game_logic->getRM()->getPlay();

	if (play_rule == 0)
	{
		return std::numeric_limits<int>::max();
	}
	else
	{
		return play_rule;
	}
}

PlayerID GameLoop::getCurrentPlayerID() const
{
	return _game_logic->getPM()->getCurrentPlayerID();
}

int GameLoop::getCardsPlayed() const
{
    return _game_logic->getPM()->getCurrentPlayer()->getCardsPlayed();
}

void GameLoop::incrementCardsPlayed()
{
	_game_logic->getPM()->getCurrentPlayer()->incrementCardsPlayed();
}

void GameLoop::nextPlayer()
{
	_game_logic->switchPlayer();
	_game_logic->getPM()->nextPlayer(_game_logic->getRM()->getPlayOrder());
}

SessionData	GameLoop::run()
{
	 auto begin = chrono::high_resolution_clock::now();

	_game_logic->getCCM()->reshuffle();

	for (Player p : _game_logic->getPM()->getPlayers())
    {
        _game_logic->drawCard(p.getID());
        _game_logic->drawCard(p.getID());
        _game_logic->drawCard(p.getID());
    }
	try
	{
		while (executePlayerTurn(getCurrentPlayerID()) == GameState::CONTINUE)
		{
			nextPlayer();
		}
	}
	catch(std::logic_error & error)
	{
		std::cerr << error.what();
	}

	string gamestate;

	if (_game_logic->getCurrentGameState() == GameState::CONTINUE)
	{
		gamestate = "CONTINUE";
	}
	else if (_game_logic->getCurrentGameState() == GameState::QUIT)
	{
		gamestate = "QUIT";
	}
	else if (_game_logic->getCurrentGameState() == GameState::GAME_OVER)
	{
		gamestate = "GAME_OVER";
	}
	else
	{
		gamestate = "INVALID GAMESTATE";
	}

	cerr << "Ending session. Gamestate: " << gamestate << endl;

 	auto end = chrono::high_resolution_clock::now();

    return SessionData(_game_logic->getPM()->getWinningPlayer(),
    				   _game_logic->getPM()->getPlayerStats(),
    				   _game_logic->getCurrentGameState(),
    				   std::chrono::duration_cast<chrono::seconds>(end - begin).count()
    				   );
}

GameState GameLoop::executePlayerTurn(PlayerID pid)
{
	checkTriggeredRules(RuleTrigger::PRE_DRAW);

	drawCards(getCurrentPlayerID(), getDrawNO());

	for (int i{0}; i < getDrawNO(); ++i)
	{
        _game_logic->getPM()->getCurrentPlayer()->incrementCardsDrawn();
	}
	checkTriggeredRules(RuleTrigger::POST_DRAW);
	checkTriggeredRules(RuleTrigger::PRE_PLAY);
	
 	while (getCardsPlayed() < getPlayNO() && _game_logic->getCCM()->getSize(getCurrentPlayerID().getString() + "_hand") != 0 && _game_logic->getCurrentGameState() == GameState::CONTINUE) // played_cards ligger i player.
 	{
 		_game_logic->playCard();
 	}
 	return _game_logic->getCurrentGameState();
}

void GameLoop::checkTriggeredRules(RuleTrigger rule)
{
	_game_logic->checkRules(rule);
}
