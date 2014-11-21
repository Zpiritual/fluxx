#ifndef DRAW_H
#define DRAW_H

#include "Effect.h"
#include <iostream>
class Draw: public Effect {
private:
	int _draw, _play, _discard;
	bool _inflation;
public:
	Draw(int draw, int play, int discard, bool inflation = true):_draw{draw}, _play{play}, _discard{discard}, _inflation{inflation}
	{}
	Draw() 							= default;
	Draw(const Draw&) 				= default;
	Draw (Draw&&) 					= default;

	Draw& operator= (const Draw&) 	= default;
	Draw& operator= (Draw&&) 		= default;

	~Draw() 						= default;

	//virtual void execute(GameLoop * game)
	//{
	//	std::cout << "Draw: " << _draw << "Play: " << _play << "Discard: " << _discard << "Inflation: " << _inflation << "\n";
	//}
};

#endif