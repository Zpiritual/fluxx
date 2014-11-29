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

void GameLogic::addRule(const CardID cid, const Effect* effect, const RuleTrigger trigger)
{
	//Add rule to RM
		cout << "Added Rule:" << cid.val << (*effect).val << endl;
	_rm->addRule(new TriggeredRule(cid,trigger,effect));
}

void GameLogic::removeRule(const CardID cid)
{
	//Move the card from Rules to Trash
	_ccm->moveCard(CardContainerID("Rules"), CardContainerID("Trash"), cid);
	//Bypass effect stack and run from executeEffect
		addEffect(*(_cm->getCard(cid)->getEffects().end()-1));
		executeNextEffect();
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
	//Fråga GUI om kort-id osv.
	CardID cid = requestPlayerInput(_pm->getCurrentPlayer()->getID(),ccid);

	//Spela det givna kortet.
	//if a Goal card is placed check if there is room for it
	//if not ask what card to replace
	if(_cm->getCard(cid)->getType() == "GOAL")
	{
		if(_ccm->getSize(CardContainerID("Goal")) > _rm->getGoalLimmit())
		{
			_ccm->moveCard(CardContainerID("Goal"), CardContainerID("Trash"),requestPlayerInput(_pm->getCurrentPlayer()->getID(),CardContainerID("Goal")));
		}
			_ccm->moveCard(ccid, CardContainerID("Goal"),cid);
			//Add effect
	}
	//If a rule is played, execute the first effect, the middle effects handles by the first effect, the last effect eecutes 
	//when the card is removed
	else if(_cm->getCard(cid)->getType().compare("RULE") == 0)
	{
		addEffect(_cm->getCard(cid)->getEffects().at(0));
		executeNextEffect();
		_ccm->moveCard(ccid, CardContainerID("Rules"),cid);
		cout << "===Cards in Rules:===" << endl;
		for(auto i: _ccm->getCards(CardContainerID("Rules")))
		{
			cout << i.val << ", ";
		}
		cout << "\n====================" << endl;
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

const CardID GameLogic::requestPlayerInput(const PlayerID pid, const CardContainerID conid) const
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

void GameLogic::checkRules(RuleTrigger rt)
{
	cout << "Check rules" << endl;
	//TODO - waiting for RuleManager to be completed
	for(const Effect* e: _rm->getTriggeredRules(rt))
	{
		addEffect(*e);

	}
	resolveEffects();
}


void GameLogic::resolveEffects()
{
	while(!effect_queue.empty())
	{
		std::cout << "not empty" << std::endl;
		executeNextEffect();
	}
}


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
			_ccm->drawCard(CardContainerID(ccid));
		}

		for(int i = 0 ; i < p2; i++)
		{
			playCard(_pm->getCurrentPlayer()->getID());
		}
		cout << "trash cards: " << endl;
		for(int i = 0 ; i < p3; i++)
		{
			_ccm->moveCard(CardContainerID(ccid), CardContainerID("Trash"), requestPlayerInput(_pm->getCurrentPlayer()->getID(),CardContainerID(ccid)));
		}

		for(CardID cid: _ccm->getCards(CardContainerID(ccid)))
		{
			_ccm->moveCard(CardContainerID(ccid), CardContainerID(_pm->getCurrentPlayer()->getID().getString() + "_hand"), cid);
		}

		cout <<"Size of: "<< ccid<<" " <<  getCCM()->getSize(CardContainerID("tempA")) << endl;
		std::cout << "Executed: " << effect.val << std::endl;
	}
	else if(identifier.compare("Redraw") == 0)
	{
		cout << "Discard and Draw" << endl;
		for(CardID i: _ccm->getCards(CardContainerID(_pm->getCurrentPlayer()->getID().getString()  + "_hand")))
		{
			_ccm->moveCard(CardContainerID(_pm->getCurrentPlayer()->getID().getString() + "_hand"),CardContainerID("Trash"), i);
			drawCard(_pm->getCurrentPlayer()->getID());
		}
	}
	else if(identifier.compare("AddTriggeredRule") == 0)
	{
		int p1;
		string p2;
		ss >> p1 >> p2;
		RuleTrigger rt;
		if(identifier.compare("PRE_DRAW"))
			rt = RuleTrigger::PRE_DRAW;
		else if(identifier.compare("POST_DRAW"))
			rt = RuleTrigger::POST_DRAW;
		else if(identifier.compare("PRE_PLAY"))
			rt = RuleTrigger::PRE_PLAY;
		else if(identifier.compare("TURN_END"))
			rt = RuleTrigger::TURN_END;
		else
			throw std::logic_error("Tried to add TriggeredRule without RuleTrigger");
		addRule(CardID(p1),&(_cm->getCard(CardID(p1))->getEffects().at(1)), rt);
	}
	else if(identifier.compare("RemoveTriggeredRule") == 0)
	{
		int p1;
		ss >> p1;
		removeRule(CardID(p1));
	}
	else if(identifier.compare("GameLimitModifier") == 0)
	{
		string p1;
		int p2;
		ss >> p1 >> p2;
		cout << "conflict: " << p1 << endl;
		for(auto i: _ccm->getCards(CardContainerID("Rules")))
		{ 
			if(_cm->getCard(i)->getSubtype().compare(p1) == 0)
				removeRule(i);
		}
		if(p1.compare("Play") == 0)
			_rm->setPlay(p2);
		if(p1.compare("Draw") == 0)
			_rm->setDraw(p2);
		if(p1.compare("Keeper") == 0)
			_rm->setKeeperLimit(p2);
		if(p1.compare("Hand") == 0)
			_rm->setPlay(p2);
		if(p1.compare("Goal") == 0)
			_rm->setGoalLimmit(p2);
		if(p1.compare("Inflation") == 0)
			_rm->setInflation(p2);
		if(p1.compare("PlayOrder") == 0)
			if(p2 == 1) 
				_rm->setPlayOrder(Direction::CLOCKWISE);
			else 
				_rm->setPlayOrder(Direction::COUNTERCLOCKWISE);
	}
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
