#include "GameLogic.h"
#include <iostream>
#include <string>

GameLogic::GameLogic(const Deck* deck, const int players)
{
	_ccm = new CardContainerManager(deck);
	_cm = new CardManager(deck);
	_rm = new RuleManager();
	_pm = new PlayerManager(players);

// Vi skulle behöva access till "alla spelare" från PlayerManager, så att vi kan iterera över dem.
//On it // martin

	 for(Player p : _pm->getPlayers())
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
	//string from effect
	//stringstream ss (effect)
	//string temp for identifier
	//ss >> temp
	//if(temp == EffectIdentifier)
	//int t1, t2, t3, .. , tn
	//ss >> t1, t2, t3, ... , tn
	//call functions with paramters
	//end effect
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

void GameLogic::playCard(const PlayerID pid)
{
	//Fråga GUI om kort-id osv.
	CardID cid = requestPlayerInput(CardContainerID(pid.getString() + "_hand"));
	//Spela det givna kortet.
		//std::cout << std::flush <<"|" <<_cm->getCard(cid)->getType() << "|"<< " "<< (_cm->getCard(cid)->getType() == "ḰEEPER") << std::endl;
	//if a Goal card is placed check if there is room for it
	//if not ask what card to replace
	if(_cm->getCard(cid)->getType() == "GOAL")
	{
		if(_ccm->getSize(CardContainerID("Goal")) > _rm->getGoalLimmit())
		{
			_ccm->moveCard(CardContainerID("Goal"), CardContainerID("Trash"),requestPlayerInput(CardContainerID("Goal")));
		}
			_ccm->moveCard(CardContainerID(pid.getString() + "_hand"), CardContainerID("Goal"),cid);
			//Add effect
	}
	//If a rule is played, execute the first effect, the middle effects handles by the first effect, the last effect eecutes 
	//when the card is removed
	else if(_cm->getCard(cid)->getType() == "RULE")
	{
		addEffect(_cm->getCard(cid)->getEffects().at(0));
		executeNextEffect();
		_ccm->moveCard(CardContainerID(pid.getString() + "_hand"), CardContainerID("Rules"),cid);
		//Must run last effect when removed
	}
	//If a action is played, put all the effects in the effect qeue
	else if(_cm->getCard(cid)->getType() == "ACTION")
	{
		_ccm->moveCard(CardContainerID(pid.getString() + "_hand"), CardContainerID("Trash"),cid);
		for(Effect e: _cm->getCard(cid)->getEffects())
			addEffect(e);
	}
	//If Keeper is played, do nothing.
	else if(_cm->getCard(cid)->getType().compare("ḰEEPER"))
	{
		std::cout << "Playing a Keeper" << std::endl;
		_ccm->moveCard(CardContainerID(pid.getString() + "_hand"), CardContainerID(pid.getString() + "_keepers"),cid);

	}
	//Else throw exception

	//Execute effects
	resolveEffects();
}

// void GameLogic::playCard(const PlayerID pid, const CardID cid)
// {
	
// 	if(getCM()->getCard(cid)->getType() == "KEEPER")
// 	{
// 		getCCM()->moveCard(getPM()->getPlayer(pid).getContainerID(), CardContainerID(pid.val + "_keepers"),cid);
// 		//std::cout << "Played a KEEPER \nID: " << cid.val << std::endl;
// 	}
// 	else if(getCM()->getCard(cid)->getType() == "RULE")
// 	{
// 		getCCM()->moveCard(getPM()->getPlayer(pid).getContainerID(), CardContainerID("Rules"),cid);
// 		//std::cout << "Played a RULE \nID: " << cid.val << std::endl;
// 	}
// 	else if(getCM()->getCard(cid)->getType() == "ACTION")
// 	{
// 		getCCM()->moveCard(getPM()->getPlayer(pid).getContainerID(), CardContainerID("Trash"), cid);
// 		//std::cout << "Played an ACTION \nID: " << cid.val << std::endl;
// 	}
// 	else if(getCM()->getCard(cid)->getType() == "GOAL")
// 	{
// 		getCCM()->moveCard(getPM()->getPlayer(pid).getContainerID(), CardContainerID("Goals"),cid);
// 		//std::cout << "Played a GOAL \nID: " << cid.val << std::endl;
// 	}
	
// }

const CardID GameLogic::requestPlayerInput(const CardContainerID conid) const
{
	//GUI request
	for(const CardID id: _ccm->getCards(conid))
		std::cout << id.val << ", ";
	std::cout << std::endl;
	int tmp;
	std::cin >> tmp;
	return CardID(tmp);
}

void GameLogic::drawCard(const PlayerID pid)
{
	//std::cout << getPM()->getPlayer(pid).getContainerID().val << std::endl;
	getCCM()->drawCard(getPM()->getPlayer(pid)->getID().getString()+"_hand");
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

// void GameLogic::checkRules(RuleTrigger rule)
// {
// _rm->clearRules();
// 	for(CardID i: _ccm->getCards(CardContainerID("Rules")))
// 	{
// 		_rm->addRule(_cm->getCard(i));
// 	}
// 	std::vector<Effect> effects = _rm->checkRules(rule);
// 	for(auto i: effects)
// 		addEffect(i);
// }

const PlayerID GameLogic::getNextPlayer()
{
	getPM()->nextPlayer();
return getPM()->getCurrentPlayer()->getID();
}
