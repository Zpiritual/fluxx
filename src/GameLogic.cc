	#include "GameLogic.h"

	GameLogic::GameLogic(const Deck * deck, const std::vector<Player> players)
	{
		_ccm = new CardContainerManager(deck);
		_cm = new CardManager(deck);
		_rm = new RuleManager();
		_pm = new PlayerManager(players);
	}

	GameLogic::~GameLogic()
	{
		delete	_ccm;
		delete	_cm;
		delete	_rm;
		delete	_pm;
	}

	void GameLogic::nextEffect()
	{
	effect_queue.front()->execute(this);
	effect_queue.pop_front();	 
	}

	void GameLogic::addEffect(Effect * effect)
	{
		effect_queue.push_front(effect);
	}

	CardContainerManager* GameLogic::getCCM()
	{
		return _ccm;
	}

	CardManager*		  GameLogic::getCM()
	{
		return _cm;
	}

	RuleManager*		  GameLogic::getRM()
	{
		return _rm;
	}

	PlayerManager*		  GameLogic::getPM()
	{
		return _pm;
	}