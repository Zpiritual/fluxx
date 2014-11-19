	#include "GameLogic.h"
	void GameLogic::nextEffect()
	{
	effect_queue.front()->execute(this);
	effect_queue.pop_front();	 
	}

	void GameLogic::newEffect(Effect * effect)
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