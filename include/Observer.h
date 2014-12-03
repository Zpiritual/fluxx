#ifndef OBSERVER_H
#define OBSERVER_H

#include "enums.h"
#include "CardContainerID.h"
#include "CardID.h"
#include <iostream>
class Observer
{
private:

public:
	virtual void onNotify(const CardContainerID &, const CardContainerID &,const CardID &, const Event) = 0;
	virtual ~Observer()
	{
	}
};

#endif