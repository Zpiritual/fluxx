#include "GameLogic.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
GameLogic::GameLogic(Gui * gui, const Deck * deck, const int players)
:
_currentGameState{GameState::CONTINUE}
{
    _gui = gui;
    _ccm = new CardContainerManager(deck);
    _ccm->addObserver(this);
    _cm = new CardManager(deck);
    _rm = new RuleManager();
    _pm = new PlayerManager(players);

    for (Player p : _pm->getPlayers())
    {
        drawCard(p.getID());
        drawCard(p.getID());
        drawCard(p.getID());
    }

}

GameLogic::~GameLogic()
{
    delete  _ccm;
    delete  _cm;
    delete  _rm;
    delete  _pm;
}

void GameLogic::addEffect(Effect effect)
{

    effect_queue.push_front(effect);
}

void GameLogic::addRule(const CardID cid, const Effect *effect, const RuleTrigger trigger)
{
    //Add rule to RM
    cout << "Added Rule:" << cid.val << (*effect).val << endl;
    _rm->addRule(new TriggeredRule(cid, trigger, effect));
}

void GameLogic::removeRule(const CardID cid)
{
    //Move the card from Rules to Trash
    _ccm->moveCard(CardContainerID("Rules"), CardContainerID("Trash"), cid);
    //Bypass effect stack and run from executeEffect
    addEffect(*(_cm->getCard(cid)->getEffects().end() - 1));
    executeNextEffect();
}

void GameLogic::playCard(const PlayerID pid)
{
    string ccids;
    //Kollar efter specialiserade containrar
    if (getCCM()->getSize(CardContainerID("tempB")) > 0)
        ccids = "tempB";
    else if (getCCM()->getSize(CardContainerID("tempA")) > 0)
        ccids = "tempA";
    else
        ccids = pid.getString() + "_hand";

    CardContainerID ccid(ccids);
    if (_ccm->getSize(ccid) == 0)
        throw std::logic_error("Playing from empty Container: " + ccids);
    //Fråga GUI om kort-id osv.

    CardID cid = pickCard(_pm->getCurrentPlayer()->getID(), ccid);
    cout << "CARD PICKED: " << cid.val << endl;
    //Spela det givna kortet.
    //if a Goal card is placed check if there is room for it
    //if not ask what card to replace
    if (_cm->getCard(cid)->getType().compare("GOAL") == 0)
    {
        if (_ccm->getSize(CardContainerID("Goal")) > _rm->getGoalLimmit())
        {
            _ccm->moveCard(CardContainerID("Goal"), CardContainerID("Trash"), pickCard(_pm->getCurrentPlayer()->getID(), CardContainerID("Goal")));
        }
        addEffect(_cm->getCard(cid)->getEffects().at(0));
        executeNextEffect();
        _ccm->moveCard(ccid, CardContainerID("Goal"), cid);
        cout << "==Cards in Goals:===" << endl;
        for (auto i : _ccm->getCards(CardContainerID("Goal")))
        {
            cout << i.val << ", ";
        }
        cout << "\n====================" << endl;
    }
    //If a rule is played, execute the first effect, the middle effects handles by the first effect, the last effect eecutes
    //when the card is removed
    else if (_cm->getCard(cid)->getType().compare("RULE") == 0)
    {
        addEffect(_cm->getCard(cid)->getEffects().at(0));
        executeNextEffect();
        _ccm->moveCard(ccid, CardContainerID("Rules"), cid);
        cout << "===Cards in Rules:===" << endl;
        for (auto i : _ccm->getCards(CardContainerID("Rules")))
        {
            cout << i.val << ", ";
        }
        cout << "\n====================" << endl;
        //Must run last effect when removed
    }
    //If a action is played, put all the effects in the effect qeue
    else if (_cm->getCard(cid)->getType().compare("ACTION") == 0)
    {
        std::cout << "Playing a Action" << std::endl;
        _ccm->suspendCard(ccid,cid);
        for (Effect e : _cm->getCard(cid)->getEffects())
            addEffect(e);
        //Execute effects
        resolveEffects();
        _ccm->unSuspendCard(CardContainerID("Trash"));
        cout << "Action done!" << endl;
    }
    //If Keeper is played, do nothing.
    else if (_cm->getCard(cid)->getType().compare("KEEPER") == 0)
    {
        std::cout << "Playing a Keeper" << std::endl;
        _ccm->moveCard(ccid, CardContainerID(pid.getString() + "_keepers"), cid);

    }
    //Else throw exception

    //Execute effects
    resolveEffects();
}

const CardID GameLogic::pickCard(const PlayerID pid, const CardContainerID container) const
{
    BoardSnapshot snapshot(makeBoardSnapshot());

    cerr << "Querying UI for a card." << endl;

    const CardID id = _gui->pickCard(&snapshot, container, pid);

    cerr << "Recieved CardID: " << id.val << endl;

    return id;
}

const PlayerID GameLogic::pickPlayer() const
{
    BoardSnapshot snapshot(makeBoardSnapshot());
    const PlayerID id = _gui->pickPlayer(&snapshot);
    return id;
}

void GameLogic::switchPlayer()
{
    BoardSnapshot snapshot(makeBoardSnapshot());
    _gui->nextPlayer(&snapshot);
}

void GameLogic::drawCard(const PlayerID pid)
{
    //std::cout << getPM()->getPlayer(pid).getContainerID().val << std::endl;
    _ccm->drawCard(pid.getString() + "_hand");
    _pm->getCurrentPlayer()->incrementCardsDrawn();

}

void GameLogic::checkRules(RuleTrigger rt)
{
    //cout << "Check rules" << endl;
    //TODO - waiting for RuleManager to be completed
    for (const Effect *e : _rm->getTriggeredRules(rt))
    {
        addEffect(*e);

    }
    resolveEffects();
}


void GameLogic::resolveEffects()
{
    while (!effect_queue.empty())
    {
        //std::cout << "not empty" << std::endl;
        executeNextEffect();
    }
}


const PlayerID GameLogic::getNextPlayer()
{
    getPM()->nextPlayer();
    return getPM()->getCurrentPlayer()->getID();
}

void GameLogic::executeNextEffect()
{
    Effect e = effect_queue.front();
    effect_queue.pop_front();
    cout << "Effect to Execute: " << e.val << endl;
    executeEffect(e);

}

void GameLogic::executeEffect(const Effect &effect)
{
    std::stringstream ss(effect.val);
    string identifier;
    ss >> identifier;
    
    if (identifier.compare("DrawAndPlay") == 0)
    {
        int draw, play, trash;
        ss >> draw >> play >> trash;
        effect_DrawAndPlay(draw, play, trash);
    }
    else if (identifier.compare("Redraw") == 0)
    {
        effect_Redraw();
    }
    else if (identifier.compare("AddTriggeredRule") == 0)
    {
        int card_id;
        string trigger;
        ss >> card_id >> trigger;
        effect_AddTriggeredRule(card_id, trigger);
    }
    else if (identifier.compare("RemoveTriggeredRule") == 0)
    {
        int card_id;
        ss >> card_id;
        effect_RemoveTriggeredRule(card_id);
    }
    else if (identifier.compare("ModifyRule") == 0)
    {
        string rule_type;
        int value;
        ss >> rule_type >> value;
        effect_ModifyRule(rule_type, value);
    }
    else if (identifier.compare("TakeCard") == 0)
    {
        int take, play, trash;
        ss >> take >> play >> trash;
        effect_TakeAndPlay(take, play, trash);
    }
    else if (identifier.compare("EmptyContainer") == 0)
    {
        string container;
        ss >> container;
        effect_EmptyContainer(container);
    }
    else if (identifier.compare("BooleanKeeperCheck") == 0)
    {
        vector<int> AKeepers;
        vector<int> NKeepers;
        int tmp;
        int AKeepers_size;
        int NKeepers_size;
        ss >> AKeepers_size;
        ss >> NKeepers_size;
        for(int i = 0; i < AKeepers_size;i++)
        {
            ss >> tmp;
            AKeepers.push_back(tmp);
        }
        for(int i = 0; i < NKeepers_size;i++)
        {
            ss >> tmp;
            NKeepers.push_back(tmp);
        }
    }
    else
    {
        throw std::logic_error("GameLogic::executeEffect() - Undefined Effect");
    }
}

void GameLogic::onNotify(const CardContainerID &cc1, const CardContainerID &cc2 , const Event event)
{
    switch (event)
    {
    case Event::CARD_MOVED:
        checkRules(RuleTrigger::GOAL);
        //cout << "Card moved!" << endl;
        for (Player p : _pm->getPlayers())
        {
            if (p.getID() != _pm->getCurrentPlayer()->getID())
            {
                cout << cc1.val << " " << cc2.val << endl;
                //Hand Limit check
                while (_ccm->getSize(CardContainerID(p.getID().getString() + "_hand")) > _rm->getHandLimit())
                {
                    cout << "Must remove from hand player: " << p.getID().getString() << ":\t";
                    CardContainerID ccid1(p.getID().getString() + "_hand");
                    CardContainerID ccid2("Trash");
                    _ccm->moveCard(ccid1, ccid2, pickCard(p.getID(), ccid1));
                    cout << "\n";
                }
                //Keeper Limit check
                while (_ccm->getSize(CardContainerID(p.getID().getString() + "_keepers")) > _rm->getKeeperLimit())
                {
                    cout << "Must remove from keepers player: " << p.getID().getString() << ":\t";
                    CardContainerID ccid1(p.getID().getString() + "_keepers");
                    CardContainerID ccid2("Trash");
                    _ccm->moveCard(ccid1, ccid2, pickCard(p.getID(), ccid1));
                    cout << "\n";
                }
            }
        }
        break;
    }
}
const GameState GameLogic::getCurrentGameState() const
{
    return _currentGameState;
}

const BoardSnapshot GameLogic::makeBoardSnapshot()const 
{
	return BoardSnapshot(_ccm->getContainers(), (int)(_pm->getPlayers().size()), _pm->getCurrentPlayer()->getID(), _pm->getCurrentPlayer()->getCardsPlayed(), _rm->getPlay(),_rm->getPlayOrder());
}

CardContainerManager *GameLogic::getCCM()
{
    return _ccm;
}

CardManager *GameLogic::getCM()
{
    return _cm;
}

RuleManager *GameLogic::getRM()
{
    return _rm;
}

PlayerManager *GameLogic::getPM()
{
    return _pm;
}

void GameLogic::effect_DrawAndPlay(int draw, int play, int trash)
{
    string ccid;
    
    if (getCCM()->getSize(CardContainerID("tempA")) == 0)
    {
        ccid = "tempA";
    }
    else if (getCCM()->getSize(CardContainerID("tempB")) == 0)
    {
        ccid = "tempB";
    }
    else
    {
        throw std::logic_error("effect_DrawAndPlay() - No empty Temp CardContainer!");
    }
    
    for (int i = 0 ; i < draw ; i++)
    {
        _ccm->drawCard(CardContainerID(ccid));
    }

    for (int i = 0 ; i < play; i++)
    {
        playCard(_pm->getCurrentPlayer()->getID());
    }
    
    for (int i = 0 ; i < trash; i++)
    {
        _ccm->moveCard(CardContainerID(ccid), CardContainerID("Trash"), pickCard(_pm->getCurrentPlayer()->getID(), CardContainerID(ccid)));
    }

    //Återstående kort flyttas till spelarens hand.
    for (CardID cid : _ccm->getCards(CardContainerID(ccid)))
    {
        _ccm->moveCard(CardContainerID(ccid), CardContainerID(_pm->getCurrentPlayer()->getID().getString() + "_hand"), cid);
    }
}

void GameLogic::effect_Redraw()
{
    std::vector<CardID> v;

    for (CardID i : _ccm->getCards(CardContainerID(_pm->getCurrentPlayer()->getID().getString()  + "_hand")))
    {
        v.push_back(i);
    }

    for (CardID i : v)
    {
        _ccm->moveCard(CardContainerID(_pm->getCurrentPlayer()->getID().getString() + "_hand"), CardContainerID("Trash"), i);
    }

    for (unsigned i = 0; i < v.size(); ++i)
    {
        drawCard(_pm->getCurrentPlayer()->getID());
    }
}

void GameLogic::effect_AddTriggeredRule(int card_id, string trigger)
{
    RuleTrigger rt;

    if (trigger.compare("PRE_DRAW"))
    {
        rt = RuleTrigger::PRE_DRAW;
    }
    else if (trigger.compare("POST_DRAW"))
    {
        rt = RuleTrigger::POST_DRAW;
    }
    else if (trigger.compare("PRE_PLAY"))
    {
        rt = RuleTrigger::PRE_PLAY;
    }
    else if (trigger.compare("TURN_END"))
    {
        rt = RuleTrigger::TURN_END;
    }
    else
    {
        throw std::logic_error("GameLogic::effect_AddTriggeredRule() - Tried to add TriggeredRule without RuleTrigger");
    }
    
    addRule(CardID(card_id), &(_cm->getCard(CardID(card_id))->getEffects().at(1)), rt);
}

void GameLogic::effect_RemoveTriggeredRule(int card_id)
{
    removeRule(CardID(card_id));
}

void GameLogic::effect_ModifyRule(string rule_type, int value)
{
    for (auto i : _ccm->getCards(CardContainerID("Rules")))
    {
        if (_cm->getCard(i)->getSubtype().compare(rule_type) == 0)
        {
            removeRule(i);
        }
    }

    if (rule_type.compare("Play") == 0)
    {
        _rm->setPlay(value);
    }
    else if (rule_type.compare("Draw") == 0)
    {
        _rm->setDraw(value);
     
        while (_pm->getCurrentPlayer()->getCardsDrawn() < _rm->getDraw())
        {
            drawCard(_pm->getCurrentPlayer()->getID());
        }
    }
    else if (rule_type.compare("Keeper") == 0)
    {
        _rm->setKeeperLimit(value);
    }
    else if (rule_type.compare("Hand") == 0)
    {
        _rm->setHandLimit(value);
    }
    else if (rule_type.compare("Goal") == 0)
    {
        _rm->setGoalLimmit(value);
    }
    else if (rule_type.compare("Inflation") == 0)
    {
        _rm->setInflation(value);
    }
    else if (rule_type.compare("PlayOrder") == 0)
    {
        if (value == 1)
        {
            _rm->setPlayOrder(Direction::CLOCKWISE);
        }
        else
        {
            _rm->setPlayOrder(Direction::COUNTERCLOCKWISE);
        }
    }
    else
    {
        throw std::logic_error("GameLogic::effect_ModifyRule() - No valid rule type.");
    }
}

void GameLogic::effect_TakeAndPlay(int take, int play, int trash)
{
    string ccid;
    
    if (getCCM()->getSize(CardContainerID("tempA")) == 0)
    {
        ccid = "tempA";
    }
    else if (getCCM()->getSize(CardContainerID("tempB")) == 0)
    {
        ccid = "tempB";
    }
    else
    {
        throw std::logic_error("GameLogic::effect_TakeAndPlay() - No available temp container.");
    }
    
    const CardContainerID temp_container(ccid);
    const CardContainerID target(pickPlayer().getString()+"_hand");
    const PlayerID current_player(_pm->getCurrentPlayer()->getID());

    for (int i = 0 ; (i < take) && (_ccm->getSize(target) > 0); ++i)
    {
        _ccm->moveCard(target, temp_container, _ccm->getRandomCard(target));
    }

    for (int i = 0; i < play; ++i)
    {
        playCard(current_player);
    }

    for (int i = 0; i < trash; ++i)
    {
        _ccm->moveCard(temp_container, CardContainerID("Trash"), pickCard(current_player, temp_container));
    }

    CardContainerID player_hand(current_player.getString()+"_hand");

    while (_ccm->getSize(temp_container) > 0)
    {
        _ccm->moveCard(temp_container, player_hand, _ccm->getRandomCard(player_hand));
    }
}

void GameLogic::effect_EmptyContainer(string container)
{
    _ccm->clearContainer(CardContainerID(container));
}

void GameLogic::effect_BooleanKeeperCheck(vector<int> &AKeepers,vector<int> &NKeepers)
{
    bool firstCheck = false;
    string winningPlayer;
    for(Player i: _pm->getPlayers())
    {
        CardContainerID cpkid(i.getID().getString() + "_keepers");
        int icheck = 0;
        for(int j: AKeepers)
        {
            if(find(_ccm->getCards(cpkid).begin(),_ccm->getCards(cpkid).end(), CardID(j)) != _ccm->getCards(cpkid).end())
                icheck++;
        }
        if(icheck == AKeepers.size())
        {
             firstCheck = true;
             winningPlayer = i.getID().getString();
        }
    }
    bool secondCheck = false;
    int icheck = 0;
    for(Player i: _pm->getPlayers())
    {
        CardContainerID cpkid(i.getID().getString() + "_keepers");
        for(int j: NKeepers)
        {
            if(find(_ccm->getCards(cpkid).begin(),_ccm->getCards(cpkid).end(), CardID(j)) != _ccm->getCards(cpkid).end())
                icheck++;
        }
    }
    if(icheck == NKeepers.size())
    secondCheck = true;
    if(firstCheck && secondCheck)
    {
        _currentGameState = GameState::GAME_OVER;
        cout << "GAME OVER!! WINNIGN PLAYER: " << winningPlayer << " It's finaly over!" << endl;
    }
}
