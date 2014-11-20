//Changelog
//2014--11-20
//moved constructor and destructor to .cc
//added forward declarations
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
class Effect;
class GameLogic
{
public:
	GameLogic(const Deck * deck, const std::vector<Player> players);
	GameLogic()					= delete;
	GameLogic(const GameLogic&) = default;
	GameLogic (GameLogic&&) 	= default;

	GameLogic& operator= (const GameLogic&) = default;
	GameLogic& operator= (GameLogic&&) 		= default;

	~GameLogic();

	void nextEffect();
	void addEffect(Effect*);

	CardContainerManager* getCCM();
	CardManager*		  getCM();
	RuleManager*		  getRM();
	PlayerManager*		  getPM();
	//Not sure
	void 			playCard(const PlayerID, const CardID);
	void			drawCard(const PlayerID);
	//void 			checkRules(RuleTriggerType);
	void 			resolveEffects();
	const PlayerID 	getNextPlayer();

private:
	CardContainerManager *_ccm;
	CardManager *_cm;
	RuleManager *_rm;
	PlayerManager *_pm;
	std::deque<Effect*> effect_queue;
};
#endif