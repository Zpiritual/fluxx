#include "PlayerID.h"

std::string PlayerID::getString() const
{
	if (val == PlayerIdentifier::Player1)
		return "Player1";
	if (val == PlayerIdentifier::Player2)
		return "Player2";
	if (val == PlayerIdentifier::Player3)
		return "Player3";
	if (val == PlayerIdentifier::Player4)
		return "Player4";
	if (val == PlayerIdentifier::Player5)
		return "Player5";
	else
		return "Player6";
}

int PlayerID::getInt() const
{
	if (val == PlayerIdentifier::Player1)
		return 1;
	if (val == PlayerIdentifier::Player2)
		return 2;
	if (val == PlayerIdentifier::Player3)
		return 3;
	if (val == PlayerIdentifier::Player4)
		return 4;
	if (val == PlayerIdentifier::Player5)
		return 5;
	else
		return 6;
}