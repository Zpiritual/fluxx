#ifndef SUBJECT_H
#define SUBJECT_H
#include "Observer.h"
#include "CardContainerID.h"
#include <vector>
#include <algorithm>
#include "enums.h"
class Subject
{
private:
	std::vector<Observer*> _observers;
protected:
	void notify(const CardContainerID & cc1, const CardContainerID & cc2, const Event event)
	{
		for(Observer* o: _observers)
		{
			o->onNotify(cc1,cc2,event);
		}
	}
public:
	void addObserver(Observer * o)
	{
		if(std::find(_observers.begin(), _observers.end(), o) == _observers.end())
			_observers.push_back(o);
	}
	void removeObserver(Observer * o)
	{
		_observers.erase(std::find(_observers.begin(), _observers.end(), o));
	}
	~Subject()
	{
		for(auto i: _observers)
		{
			delete i;
		}
	}
};
#endif