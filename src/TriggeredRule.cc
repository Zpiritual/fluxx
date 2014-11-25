#include "TriggeredRule.h"

TriggeredRule::TriggeredRule(const CardID parent, const RuleTrigger type, const std::vector<Effect*> effects):
_parent{parent},
_type{type},
_effects{effects}
{}

const std::vector<Effect*> TriggeredRule::getEffects()
{
	return _effects;
}

const RuleTrigger TriggeredRule::getType()
{
	return _type;
}

const CardID TriggeredRule::getParent()
{
	return _parent;
}