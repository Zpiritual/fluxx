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
#include "CardContainerID.h"
#include "CardContainerManager.h"
#include "BoardSnapshot.h"
#include "CardManager.h"
#include "RuleManager.h"
#include "PlayerManager.h"
#include "enums.h"
#include "Observer.h"

class GameLogic:public Observer
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

	//Prototype functions
	void addRule(const CardID, const Effect*, const RuleTrigger);
	void removeRule(const CardID);
	const CardID pickCard(const PlayerID ,const CardContainerID) const;
	const PlayerID pickPlayer() const;
	void switchPlayer();

	CardContainerManager* getCCM();
	CardManager*		  getCM();
	RuleManager*		  getRM();
	PlayerManager*		  getPM();

	void				 playCard(const PlayerID);
	void				 drawCard(const PlayerID);
	//void 			checkRules(RuleTriggerType);
	void				 resolveEffects();
	void				 checkRules(RuleTrigger);
	//bool 			checkGoal();
	const PlayerID		 getNextPlayer();
	const BoardSnapshot makeBoardSnapshot() const;

private:
	CardContainerManager *_ccm;
	CardManager *_cm;
	RuleManager *_rm;
	PlayerManager *_pm;
	std::deque<Effect> effect_queue;
	void executeEffect(const Effect&);
	void onNotify(const CardContainerID &, const CardContainerID & , const Event);
	//Diverse effekt-funktioner, ex:
	//Draw(int draw, int play, int discard, bool inflation = true);
};

#endif