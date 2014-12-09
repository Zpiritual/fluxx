#ifndef ENUMS_H
#define ENUMS_H

enum class Direction
{
	CLOCKWISE,
	COUNTERCLOCKWISE
};

enum class RuleTrigger
{
	PRE_DRAW,
	POST_DRAW,
	PRE_PLAY,
	TURN_END,
	GOAL
};

enum class GameState
{
	CONTINUE,
	QUIT,
	GAME_OVER
};

enum class PlayerIdentifier
{
	Player1,
	Player2,
	Player3,
	Player4,
	Player5,
	Player6,
	NO_PLAYER
};

enum class Event
{
	CARD_MOVED
};

#endif