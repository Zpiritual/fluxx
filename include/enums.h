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
	POST_DRA,
	END_TURN
};

enum class gameState
{
	CONTINUE,
	GAME_OVER
};
#endif