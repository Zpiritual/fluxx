#ifndef TRIGGEREDRULE_H
#define TRIGGEREDRULE_H
#include "enums.h"
#include "Effect.h"
#include "CardID.h"
#include <vector>
class TriggeredRule
{
public:
	TriggeredRule(const CardID, const RuleTrigger, const std::vector<Effect*>);
	TriggeredRule()=delete;
	TriggeredRule(const TriggeredRule&) = default;
	TriggeredRule (TriggeredRule&&) = default;

	TriggeredRule& operator= (const TriggeredRule&) = default;
	TriggeredRule& operator= (TriggeredRule&&) = default;
	~TriggeredRule() = default;

	std::vector<Effect*> getEffects();
	RuleTrigger getType();
	CardID getParent();

private:

std::vector<Effect*> _effects;
RuleTrigger _type;	
CardID _parent;

};
#endif