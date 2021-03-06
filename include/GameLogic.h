#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Deck.h"
#include "Effect.h"
#include <vector>
#include <deque>
#include <iostream>
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
#include "gui.h"

class GameLogic : public Observer
{
public:
    GameLogic(Gui * gui, const Deck * deck, const int players);
	GameLogic()					= delete;
	GameLogic(const GameLogic&) = default;
	GameLogic (GameLogic&&) 	= default;

	GameLogic& operator= (const GameLogic&) = default;
	GameLogic& operator= (GameLogic&&) 		= default;

	~GameLogic();

	void executeNextEffect();
	void addEffect(Effect);

    void	 addRule(const CardID, Effect*, const RuleTrigger);
	void	 removeRule(const CardID);
    CardID	 pickCard(const PlayerID, const CardContainerID);
    PlayerID pickPlayer();
	void	 switchPlayer();
	bool	 playerDecision(string, string, string);

	CardContainerManager* getCCM();
	CardManager*		  getCM();
	RuleManager*		  getRM();
	PlayerManager*		  getPM();


	void		  playCard();
    void		  playCardWithID(const CardID, const CardContainerID);
	void		  drawCard(const PlayerID);
	void		  resolveEffects();
	void		  checkRules(RuleTrigger);
	BoardSnapshot makeBoardSnapshot(const PlayerID active, const CardContainerID target) const;
	BoardSnapshot makeBoardSnapshot() const;

    void effect_DrawAndPlay(int, int, int);
	void effect_Redraw();
    void effect_AddTriggeredRule(int, string);
    void effect_RemoveTriggeredRule(int);
    void effect_ModifyRule(string, int);
    void effect_TakeAndPlay(int, int, int);
	void effect_ReshuffleContainer(string);
    void effect_BooleanKeeperCheck(vector<int> &,vector<int> &);
    void effect_SpecificKeeperCheck(vector<int>);
	void effect_ContainerQuantityCheck(string, int);
	void effect_SwapPlayerContainer(string);
	void effect_TrashKeepers(int);
	void effect_TrashCardsFromContainer(int,string);
    void effect_ForceRandomPlay(int);
	void effect_MoveContainer(string, string);
	void effect_MoveCardsSubtype(string, string, string);
	void effect_MoveKeepers(int);
	void effect_RepeatTurn();
	void effect_ScramblePlayerContainer(string);
	void effect_BonusPlayerContainerQuantity(int, string, char,string);
	void effect_BonusPlayerContainerEmpty(int, string);
	void effect_RotatePlayerContainer(string);
    void effect_DrawAndDistribute(int);
    void effect_TakeAndPlayBasedOnSubtype(string, vector<string>);
    void effect_DiscardPercentileOfContainer(string,int);
    void effect_TakeRandomAndPlayFromPlayer(string,int);
    void effect_SetOrder(string);
    void effect_PlayersGiveToPlayer(int);
	void effect_SwapKeepers(int);
    
	void writeToLog(const string);

	GameState getCurrentGameState() const;

private:
    Gui * _gui;
    CardContainerManager *_ccm;
    CardManager *_cm;
	RuleManager *_rm;
	PlayerManager *_pm;
	std::deque<Effect> effect_queue;
    GameState _currentGameState;
    string _local_log;
    vector<pair<const PlayerID,const string>> _log;
	void executeEffect(const Effect&);
    void onNotify(const CardContainerID &, const CardContainerID & ,const CardID &, const Event);
};

#endif
