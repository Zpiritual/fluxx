#ifndef ENUMS_H
#define ENUMS_H

enum class Direction
{
	CW,
	CCW 
};

enum class RuleTrigger
{
	PRE_DRAW,
	POST_DRAW,
	TURN_END
};

enum class gameState
{
	CONTINUE,
	GAME_OVER
};

#endif