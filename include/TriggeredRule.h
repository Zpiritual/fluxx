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
	TriggeredRule() = delete;
	TriggeredRule(const TriggeredRule&) = default;
	TriggeredRule (TriggeredRule&&) = default;

	TriggeredRule& operator= (const TriggeredRule&) = default;
	TriggeredRule& operator= (TriggeredRule&&) = default;
	~TriggeredRule() = default;

	const std::vector<Effect*> getEffects();
	const RuleTrigger getType();
	const CardID getParent();

private:
	const CardID _parent;
	const RuleTrigger _type;
	const std::vector<Effect*> _effects;
};

#endif