//Changelog
//2014--11-20
//moved constructor and destructor to .cc
//added forward declarations
//=========

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Deck.h"
#include "Effect.h"
#include <vector>
#include <deque>
#include "Player.h"
#include "PlayerID.h"
#include "CardContainerManager.h"
#include "CardManager.h"
#include "RuleManager.h"
#include "PlayerManager.h"
#include "enums.h"

class GameLogic
{
public:
	GameLogic(const Deck * deck, const int players);
	GameLogic()					= delete;
	GameLogic(const GameLogic&) = default;
	GameLogic (GameLogic&&) 	= default;

	GameLogic& operator= (const GameLogic&) = default;
	GameLogic& operator= (GameLogic&&) 		= default;

	~GameLogic();

	void executeNextEffect();
	void addEffect(Effect);

	CardContainerManager* getCCM();
	CardManager*		  getCM();
	RuleManager*		  getRM();
	PlayerManager*		  getPM();

	//void 			playCard(const PlayerID, const CardID);
	void 			playCard(const PlayerID);
	void			drawCard(const PlayerID);
	//void 			checkRules(RuleTriggerType);
	void 			resolveEffects();
	void 			checkRules(RuleTrigger);
	//bool 			checkGoal();
	const PlayerID 	getNextPlayer();
	const CardID	requestPlayerInput(const CardContainerID) const;
private:
	CardContainerManager *_ccm;
	CardManager *_cm;
	RuleManager *_rm;
	PlayerManager *_pm;
	std::deque<Effect> effect_queue;

	//Diverse effekt-funktioner, ex:
	//Draw(int draw, int play, int discard, bool inflation = true);
};

#endif