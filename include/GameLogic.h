//Changelog
//=========
#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "Effect.h"
#include "Deck.h"
#include <vector>
#include <deque>
#include "Player.h"
#include "CardContainerManager.h"
#include "CardManager.h"
#include "RuleManager.h"
#include "PlayerManager.h"
class GameLogic
{
public:
	GameLogic(Deck * deck, const std::vector<Player> players)
	{
		_ccm = new CardContainerManager();
		_cm = new CardManager(deck);
		_rm = new RuleManager();
		_pm = new PlayerManager(players);
	}
	GameLogic()					= delete;
	GameLogic(const GameLogic&) = default;
	GameLogic (GameLogic&&) 	= default;

	GameLogic& operator= (const GameLogic&) = default;
	GameLogic& operator= (GameLogic&&) 		= default;

	~GameLogic() = default;

	void nextEffects();
	void addEffect(Effect*);

	CardContainerManager* getCCM();
	CardManager*		  getCM();
	RuleManager*		  getRM();
	PlayerManager*		  getPM();


private:
	CardContainerManager *_ccm;
	CardManager *_cm;
	RuleManager *_rm;
	PlayerManager *_pm;
	std::deque<Effect*> effect_queue;
};
#endif