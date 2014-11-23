
//NOT COMPLETE AND NEEDS ATTENTION
#ifndef RULEMANAGER_H
#define RULEMANAGER_H
#include "Effect.h"
#include <vector>
enum Direction
{
	CW = 1,
	CCW = 2
};

enum RuleTriggerType
{
	PRE_DRAW = 0,
	POST_DRAW = 1,
	END_TURN = 2
};
class Effect;
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
private:
	int _hand_limmit 	= 0;
	int _keeper_limit	= 0;
	int _goal_limit		= 0;
	int _inflation		= 0;
	int _draw			= 0;
	int _play 			= 0;
	Direction _play_direction = CW;
	std::vector<Effect*> _tiggered_rules;
};
#endif