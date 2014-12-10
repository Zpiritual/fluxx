#include "RuleManager.h"
#include <iostream>

RuleManager::~RuleManager()
{
	for(TriggeredRule* i: _triggered_rules)
		delete i;
}

int RuleManager::getHandLimit()
{
	if (_hand_limit >= std::numeric_limits<int>::max() - _inflation)
	{
		return _hand_limit;
	}
	else
	{
		return _hand_limit + _inflation;
	}
}

int RuleManager::getKeeperLimit()
{
	if (_keeper_limit >= std::numeric_limits<int>::max() - _inflation)
	{
		return _keeper_limit;
	}
	else
	{
		return _keeper_limit + _inflation;
	}
}

int RuleManager::getGoalLimit()
{
	if (_goal_limit == 0)
	{
		return std::numeric_limits<int>::max();
	}
	else
	{
		return _goal_limit;
	}
}

int RuleManager::getInflation()
{
	return _inflation;
}

int RuleManager::getDraw()
{
	if (_draw == 0)
	{
		return std::numeric_limits<int>::max();
	}
	else
	{
		return _draw + _inflation;
	}
}

int RuleManager::getPlay()
{
	if (_play == 0)
	{
		return std::numeric_limits<int>::max();
	}
	else
	{
		return _play + _inflation;
	}
}

Direction RuleManager::getPlayOrder()
{
	return _play_direction;
}

void RuleManager::setHandLimit(const int l)
{
    _hand_limit = l;
}

void RuleManager::setKeeperLimit(const int l)
{
	_keeper_limit = l;
}

void RuleManager::setGoalLimit(const int l)
{
	_goal_limit = l;
}

void RuleManager::setInflation(const int l)
{
	_inflation = l;
}

void RuleManager::setDraw(const int l)
{
	_draw = l;
}

void RuleManager::setPlay(const int l)
{
	_play = l;
}

void RuleManager::setPlayOrder(const Direction l)
{
	_play_direction = l;
}
void RuleManager::addRule(TriggeredRule* rule)
{
	_triggered_rules.push_back(rule);
}

void RuleManager::removeRule(CardID cid)
{
	for(unsigned int i = 0; i < _triggered_rules.size(); i++)
		if(_triggered_rules.at(i)->getParent() == cid)
		{
			delete _triggered_rules.at(i);
			_triggered_rules.erase(_triggered_rules.begin() + i);
		}
}

void RuleManager::clearRules()
{
	for(TriggeredRule* i: _triggered_rules)
		delete i;
	_triggered_rules.clear();
}

std::vector<Effect> RuleManager::getTriggeredRules(const RuleTrigger type)
{
	std::vector<Effect> effects;
	for(TriggeredRule* tr : _triggered_rules)
	{
		if(tr->getType() == type)
		{
            std::cout << tr->getEffect().val << std::endl;
			effects.push_back(tr->getEffect());
		}
	}
	return effects;
}
