#include "TriggeredRule.h"
	TriggeredRule::TriggeredRule(const CardID parent, const RuleTrigger type, const std::vector<Effect*> effects):
	_parent{parent},
	_type{type},
	_effects{effects}
	{}

	std::vector<Effect*> TriggeredRule::getEffects()
	{
		return _effects;
	}

	RuleTrigger 	 TriggeredRule::getType()
	{
		return _type;
	}

	CardID 		 TriggeredRule::getParent()
	{
		return _parent;
	}
