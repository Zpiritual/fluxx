#include "TriggeredRule.h"

TriggeredRule::TriggeredRule(const CardID parent, const RuleTrigger type, const Effect* effect)
	: _parent{parent}, _type{type}, _effect{effect}
{}

TriggeredRule::~TriggeredRule()
{
	delete _effect;
}

const Effect* TriggeredRule::getEffect() const
{
	return _effect;
}

const RuleTrigger TriggeredRule::getType() const
{
	return _type;
}

const CardID TriggeredRule::getParent() const
{
	return _parent;
}