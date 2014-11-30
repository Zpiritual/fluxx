#ifndef OBSERVER_H
#define OBSERVER_H
#include "enums.h"
#include "CardContainerID.h"
class Observer
{
private:

public:
	virtual void onNotify(const CardContainerID &, const CardContainerID &, const Event) = 0;
	virtual~Observer()
	{}
};
#endif