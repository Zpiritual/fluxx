#include "PlayerID.h"

std::string PlayerID::getString() const
{
	if (val == PlayerIdentifier::Player1)
		return "Player1";
	else if (val == PlayerIdentifier::Player2)
		return "Player2";
	else if (val == PlayerIdentifier::Player3)
		return "Player3";
	else if (val == PlayerIdentifier::Player4)
		return "Player4";
	else if (val == PlayerIdentifier::Player5)
		return "Player5";
	else
		return "Player6";
}

int PlayerID::getInt() const
{
	if (val == PlayerIdentifier::Player1)
		return 1;
	else if (val == PlayerIdentifier::Player2)
		return 2;
	else if (val == PlayerIdentifier::Player3)
		return 3;
	else if (val == PlayerIdentifier::Player4)
		return 4;
	else if (val == PlayerIdentifier::Player5)
		return 5;
	else
		return 6;
}