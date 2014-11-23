#ifndef EFFECT_H
#define EFFECT_H
#include "GameLogic.h"

//class GameLogic;
class Effect {
private:

public:
	Effect() 							= default;
	Effect(const Effect&) 				= default;
	Effect (Effect&&) 					= default;

	Effect& operator= (const Effect&) 	= default;
	Effect& operator= (Effect&&) 		= default;

	~Effect() 							= default;

	virtual void execute(GameLogic *) = 0;
};

#endif