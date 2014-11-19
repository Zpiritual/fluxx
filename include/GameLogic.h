//Changelog
//=========
#ifndef GAMELOGIC_H
#define GAMELOGIC_H
class GameLogic
{
public:
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