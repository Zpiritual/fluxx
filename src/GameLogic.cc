#include "GameLogic.h"
#include <iostream>
#include <sstream>
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
	string ccids;
	//Kollar efter specialiserade containrar
	if(getCCM()->getSize(CardContainerID("tempB")) > 0)
		ccids = "tempB";
	else if(getCCM()->getSize(CardContainerID("tempA")) > 0)
		ccids = "tempA";
	else
		ccids = pid.getString() + "_hand";
	CardContainerID ccid(ccids);
	cout << "Container to play from: " << ccids << " size of cotnainer: "<< getCCM()->getSize(ccid) <<  endl;

	//Fråga GUI om kort-id osv.
	CardID cid = requestPlayerInput(ccid);

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
			_ccm->moveCard(ccid, CardContainerID("Goal"),cid);
			//Add effect
	}
	//If a rule is played, execute the first effect, the middle effects handles by the first effect, the last effect eecutes 
	//when the card is removed
	else if(_cm->getCard(cid)->getType() == "RULE")
	{
		addEffect(_cm->getCard(cid)->getEffects().at(0));
		executeNextEffect();
		_ccm->moveCard(ccid, CardContainerID("Rules"),cid);
		//Must run last effect when removed
	}
	//If a action is played, put all the effects in the effect qeue
	else if(_cm->getCard(cid)->getType().compare("ACTION") == 0)
	{
			std::cout << "Playing a Action" << std::endl;
		_ccm->moveCard(ccid, CardContainerID("Trash"),cid);
		for(Effect e: _cm->getCard(cid)->getEffects())
			addEffect(e);
	}
	//If Keeper is played, do nothing.
	else if(_cm->getCard(cid)->getType().compare("KEEPER")== 0)
	{
		std::cout << "Playing a Keeper" << std::endl;
		_ccm->moveCard(ccid, CardContainerID(pid.getString() + "_keepers"),cid);

	}
	//Else throw exception

	//Execute effects
	resolveEffects();
}


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

//Used when draw card to other container than player_hand
void GameLogic::drawCard(const CardContainerID ccid)
{
	getCCM()->drawCard(ccid);
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
		std::cout << "not empty" << std::endl;
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

void GameLogic::executeNextEffect()
{
	Effect e = effect_queue.front();
	effect_queue.pop_front();
	executeEffect(e);
	cout << "Poping effect" << endl;

}
//Private Effect function
void GameLogic::executeEffect(const Effect& effect)
{
	std::stringstream ss(effect.val);
	string identifier;
	ss >> identifier;
	if(identifier.compare("DrawCard") == 0)
	{
		int p1,p2,p3;
		ss >> p1 >> p2 >> p3;
		cout << p1 << " " << p2 << " "  << p3 << endl;
		string ccid = _pm->getCurrentPlayer()->getID().getString() + "_hand";
		if(getCCM()->getSize(CardContainerID("tempA")) == 0)
		{
			ccid = "tempA";
		}
		else if(getCCM()->getSize(CardContainerID("tempB")) == 0)
		{
			ccid = "tempB";
		}
		cout << "Effect puts cards in: " << ccid << endl;
		for(int i = 0 ; i < p1 ; i++)
		{
			drawCard(CardContainerID(ccid));
		}

		for(int i = 0 ; i < p2; i++)
		{
			playCard(_pm->getCurrentPlayer()->getID());
		}
		cout << "trash cards: " << endl;
		for(int i = 0 ; i < p3; i++)
		{
			_ccm->moveCard(CardContainerID(ccid), CardContainerID("Trash"), requestPlayerInput(CardContainerID(ccid)));
		}

		for(CardID cid: _ccm->getCards(CardContainerID(ccid)))
		{
			_ccm->moveCard(CardContainerID(ccid), CardContainerID(_pm->getCurrentPlayer()->getID().getString() + "_hand"), cid);
		}

		cout <<"Size of: "<< ccid<<" " <<  getCCM()->getSize(CardContainerID("tempA")) << endl;
		std::cout << "Executed: " << effect.val << std::endl;
	}
	
}