#ifndef TRIGGEREDRULE_H
#define TRIGGEREDRULE_H

#include "enums.h"
#include "Effect.h"
#include "CardID.h"
#include <vector>

class TriggeredRule
{
public:
	TriggeredRule(const CardID, const RuleTrigger, const Effect*);

	TriggeredRule()								   = delete;
	TriggeredRule(const TriggeredRule&)			   = default;
	TriggeredRule(TriggeredRule&&)				   = default;

	TriggeredRule& operator=(const TriggeredRule&) = delete;
	TriggeredRule& operator=(TriggeredRule&&)	   = delete;
	~TriggeredRule();

    const Effect* getEffect() const;
	RuleTrigger getType() const;
	CardID getParent() const;

private:
	const CardID _parent;
	const RuleTrigger _type;
	const Effect* _effect;
};

#endif
