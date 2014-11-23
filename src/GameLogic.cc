#include "GameLogic.h"
#include <iostream>

GameLogic::GameLogic(const Deck* deck, const std::vector<Player> players)
{
	_ccm = new CardContainerManager(deck);
	_cm = new CardManager(deck);
	_rm = new RuleManager();
	_pm = new PlayerManager(players);

	for(auto p:players)
	{
		drawCard(p.getID());
		drawCard(p.getID());
		drawCard(p.getID());
	}

}

GameLogic::~GameLogic()
{
	delete	_ccm;
	delete	_cm;
	delete	_rm;
	delete	_pm;
}

void GameLogic::executeNextEffect()
{
	effect_queue.pop_front();
}

void GameLogic::addEffect(Effect effect)
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
		getCCM()->moveCard(getPM()->getPlayer(pid).getContainerID(), CardContainerID(pid.val + "_keepers"),cid);
		std::cout << "Played a KEEPER \nID: " << cid.val << std::endl;
	}
	else if(getCM()->getCard(cid)->getType() == "RULE")
	{
		getCCM()->moveCard(getPM()->getPlayer(pid).getContainerID(), CardContainerID("Rules"),cid);
		std::cout << "Played a RULE \nID: " << cid.val << std::endl;
	}
	else if(getCM()->getCard(cid)->getType() == "ACTION")
	{
		getCCM()->moveCard(getPM()->getPlayer(pid).getContainerID(), CardContainerID("Trash"), cid);
		std::cout << "Played a ACTION \nID: " << cid.val << std::endl;
	}
	else if(getCM()->getCard(cid)->getType() == "GOAL")
	{
		getCCM()->moveCard(getPM()->getPlayer(pid).getContainerID(), CardContainerID("Goals"),cid);
		std::cout << "Played a GOAL \nID: " << cid.val << std::endl;
	}
	
}

void GameLogic::drawCard(const PlayerID pid)
{
	//std::cout << getPM()->getPlayer(pid).getContainerID().val << std::endl;
	getCCM()->drawCard(getPM()->getPlayer(pid).getContainerID());
}

/*	void GameLogic::checkRules(RuleTriggerType)
{
	//TODO - waiting for RuleManager to be completed
}
*/
void GameLogic::resolveEffects()
{
	while(!effect_queue.empty())
	{
		executeNextEffect();
	}
}
//Works?
//void 			GameLogic::checkRules()
//{
//	_rm->clearRules();
//	for(CardID i: _ccm->getCards(CardContainerID("Rules")))
//	{
//		_rm->addRule(_cm->getCard(i));
//	}
//	_rm->checkRules();
//}

const PlayerID GameLogic::getNextPlayer()
{
	getPM()->nextPlayer();
return getPM()->getCurrentPlayer().getID();
}
