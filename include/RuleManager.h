#ifndef RULEMANAGER_H
#define RULEMANAGER_H
#include "Effect.h"
#include <vector>
enum Direction
{
	CW = 1,
	CCW = 2
};

class RuleManger
{
public:
	RuleManger() = delete;
	RuleManger(const RuleManger&) = default;
	RuleManger (RuleManger&&) = default;

	RuleManger& operator= (const RuleManger&) = default;
	RuleManger& operator= (RuleManger&&) = default;

	~RuleManger() = default;

	const int 		getHandLimit()		const;
	const int 		getKepperLimit() 	const;
	const int 		getGoalLimmit() 	const;
	const int 		getInflation() 		const;
	const int 		getDraw() 			const;
	const int 		getPlay() 			const;
	const Direction getPlayOrder()  	const;

	void setHandLimit(const int l);
	void setKeeperLimit(const int l);
	void setGoalLimmit(const int l);
	void setInflatio(const int l);
	void setDraw(const int l);
	void setPlay(const int l);
	void setPlayOrder(const Direction l);

private:
	int _hand_limmit;
	int _keeper_limit;
	int _goal_limit;
	int _inflation;
	int _draw;
	int _play;
	Direction _play_direction;
	std::vector<Effect*> _tiggered_rules;
};
#endif