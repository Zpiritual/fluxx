#ifndef RULEMANAGER_H
#define RULEMANAGER_H

#include "Effect.h"
#include "TriggeredRule.h"
#include "enums.h"
#include <vector>

class RuleManager
{
public:
	RuleManager()=default;
	RuleManager(const RuleManager&) = default;
	RuleManager (RuleManager&&) = default;

	RuleManager& operator= (const RuleManager&) = default;
	RuleManager& operator= (RuleManager&&) = default;
	~RuleManager() = default;

	const int 		getHandLimit()		const;
	const int 		getKepperLimit() 	const;
	const int 		getGoalLimmit() 	const;
	const int 		getInflation() 		const;
	const int 		getDraw() 			const;
	const int 		getPlay() 			const;
	const Direction getPlayOrder()  	const;

	void setHandLimit(const int);
	void setKeeperLimit(const int);
	void setGoalLimmit(const int);
	void setInflation(const int);
	void setDraw(const int);
	void setPlay(const int);
	void setPlayOrder(const Direction);
	std::vector<Effect*> getTriggeredRules(const RuleTrigger);
	//Placeholders?
	void addRule(TriggeredRule);
	void removeRule(CardID);
	void clearRules();

private:
	int _hand_limmit 	= 0;
	int _keeper_limit	= 0;
	int _goal_limit		= 0;
	int _inflation		= 0;
	int _draw			= 0;
	int _play 			= 0;
	Direction _play_direction = Direction::CW;
	std::vector<TriggeredRule> _triggered_rules;
};

#endif