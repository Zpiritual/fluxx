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

	CardManager* GameLogic::getCM()
	{
		return _cm;
	}

	RuleManager* GameLogic::getRM()
	{
		return _rm;
	}

	PlayerManager* GameLogic::getPM()
	{
		return _pm;
	}

	void GameLogic::playCard(const PlayerID pid, const CardID cid)
	{
		if(getCM()->getCard(cid)->getType() == "KEEPER")
		{
			getCCM()->moveCard(getPM()->getPlayer(pid)->getContainerID(), CardContainerID(pid + "_keepers"));
		}
		else if(getCM()->getCard(cid)->getType() == "RULE")
		{
			getCCM()->moveCard(getPM()->getPlayer(pid)->getContainerID(), CardContainerID("active_rules"));
		}
		else if(getCM()->getCard(cid)->getType() == "ACTION")
		{
			getCCM()->moveCard(getPM()->getPlayer(pid)->getContainerID(), CardContainerID(pid + "trash_heap"));
		}
		else if(getCM()->getCard(cid)->getType() == "GOAL")
		{
			getCCM()->moveCard(getPM()->getPlayer(pid)->getContainerID(), CardContainerID(pid + "goals"));
		}
	}

	void GameLogic::drawCard(const PlayerID pid)
	{
		getCCM()->drawCard(getPM()->getPlayer(pid)->getContainerID());
	}

	void GameLogic::checkRules(RuleTriggerType)
	{
		//TODO - waiting for RuleManager to be completed
	}

	void GameLogic::resolveEffects()
	{
		while(!effect_queue.empy())
		{
			nextEffect();
		}
	}

	const PlayerID GameLogic::getNextPlayer()
	{
		getPM()->nextPlayer();
	return getPM()->getCurrentPlayer()->getID();
	}
