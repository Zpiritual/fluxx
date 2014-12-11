#ifndef RULEMANAGER_H
#define RULEMANAGER_H

#include "Effect.h"
#include "TriggeredRule.h"
#include "enums.h"
#include <vector>
#include <limits>

class RuleManager
{
public:
	RuleManager()=default;
	RuleManager(const RuleManager&) = default;
	RuleManager (RuleManager&&) = default;

	RuleManager& operator= (const RuleManager&) = default;
	RuleManager& operator= (RuleManager&&) = default;
	~RuleManager();

	int 		getHandLimit()		;
	int 		getKeeperLimit() 	;
	int 		getGoalLimit() 	;
	int 		getInflation() 		;
	int 		getDraw() 			;
	int 		getPlay() 			;
	Direction	getPlayOrder()  	;

	void setHandLimit(const int);
	void setKeeperLimit(const int);
	void setGoalLimit(const int);
	void setInflation(const int);
	void setDraw(const int);
	void setPlay(const int);
	void setPlayOrder(const Direction);

    std::vector<Effect> getTriggeredRules(const RuleTrigger);
    
	void addRule(TriggeredRule*);
	void removeRule(CardID);
	void clearRules();

private:
	int _hand_limit 	= std::numeric_limits<int>::max();
	int _keeper_limit	= std::numeric_limits<int>::max();
	int _goal_limit		= 1;
	int _inflation		= 0;
	int _draw			= 1;
	int _play 			= 1;
	Direction _play_direction = Direction::CLOCKWISE;
	std::vector<TriggeredRule*> _triggered_rules;
};

#endif
