#include "GameLogic.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

GameLogic::GameLogic(Gui *gui, const Deck *deck, const int players)
    : _currentGameState {GameState::CONTINUE}
{
    _gui = gui;
    _ccm = new CardContainerManager(deck);
    _ccm->addObserver(this);
    _cm = new CardManager(deck);
    _rm = new RuleManager();
    _pm = new PlayerManager(players);
    _local_log = "";
}

GameLogic::~GameLogic()
{
    _ccm->removeObserver(this);
    delete  _ccm;
    _ccm = nullptr;
    delete  _cm;
    _cm = nullptr;
    delete  _rm;
    _rm  = nullptr;
    delete  _pm;
    _pm  = nullptr;
}

void GameLogic::addEffect(Effect effect)
{
    if (getCurrentGameState() != GameState::CONTINUE) return;
    effect_queue.push_front(effect);
}

//Only used inside effect
void GameLogic::addRule(const CardID cid, Effect *effect, const RuleTrigger trigger)
{
    if (getCurrentGameState() != GameState::CONTINUE) return;
    cerr << "Added Rule:" << cid.val << (*effect).val << endl;
    _rm->addRule(new TriggeredRule(cid, trigger, *effect));
}
//Only used inside effect
void GameLogic::removeRule(const CardID cid)
{
    if (getCurrentGameState() != GameState::CONTINUE) return;
    _rm->removeRule(cid);
}

void GameLogic::playCard()
{
    if (getCurrentGameState() != GameState::CONTINUE) return;
    string ccids;
    //Kollar efter specialiserade containrar
    if (_ccm->getSize(CardContainerID("tempB")) > 0)
        ccids = "tempB";
    else if (_ccm->getSize(CardContainerID("tempA")) > 0)
        ccids = "tempA";
    else
        ccids = _pm->getCurrentPlayer()->getID().getString() + "_hand";

    CardContainerID ccid(ccids);
    if (_ccm->getSize(ccid) == 0)
        throw std::logic_error("Playing from empty Container: " + ccids);
    //Fråga GUI om kort-id osv.

    CardID cid = pickCard(_pm->getCurrentPlayer()->getID(), ccid);
    if(cid != CardID(0))
    playCardWithID(cid, ccid);
}

void GameLogic::playCardWithID(const CardID cid, const CardContainerID ccid)
{
    if (getCurrentGameState() != GameState::CONTINUE) return;
    //Spela det givna kortet.
    //if a Goal card is placed check if there is room for it
    //if not ask what card to replace
    string str = "Played Card: ";
    str.append(_cm->getCard(cid)->getName());
    writeToLog(str);
    
    _pm->getCurrentPlayer()->incrementTotalCardsPlayed();
    _pm->getCurrentPlayer()->incrementConsecutivePlays();


    if (ccid.val.find("_hand") != string::npos)
        _pm->getCurrentPlayer()->incrementCardsPlayed();
   
    if (_cm->getCard(cid)->getType().compare("GOAL") == 0)
    {
        _ccm->suspendCard(ccid, cid);
        if (_ccm->getSize(CardContainerID("Goal")) == _rm->getGoalLimmit())
        {
            cout << "\t Goal is too big!" << _ccm->getSize(CardContainerID("Goal")) << " " <<  _rm->getGoalLimmit() <<   endl;
            CardID cid2 = pickCard(_pm->getCurrentPlayer()->getID(), CardContainerID("Goal"));
            _ccm->moveCard(CardContainerID("Goal"), CardContainerID("Trash"), cid2);
            // _rm->removeRule(cid2);
        }
        //addRule(cid, &_cm->getCard(cid)->getEffects().at(0), RuleTrigger::GOAL);
        _ccm->unSuspendCard(CardContainerID("Goal"));
        // cout << "==Cards in Goals:===" << endl;
        //  for (auto i : _ccm->getCards(CardContainerID("Goal")))
        // {
        //      cout << i.val << ", ";
        //  }
        //  cout << "\n====================" << endl;
    }
    //If a rule is played, execute the first effect, the middle effects handles by the first effect, the last effect eecutes
    //when the card is removed
    else if (_cm->getCard(cid)->getType().compare("RULE") == 0)
    {
        //addEffect(_cm->getCard(cid)->getEffects().at(0));
        //executeNextEffect();
        _ccm->suspendCard(ccid, cid);
            addEffect(*(_cm->getCard(cid)->getEffects().begin()));
            executeNextEffect();
        _ccm->unSuspendCard(CardContainerID("Rules"));
        //cout << "===Cards in Rules:===" << endl;
        // for (auto i : _ccm->getCards(CardContainerID("Rules")))
        // {
        //     cout << i.val << ", ";
        // }
        //cout << "\n====================" << endl;
        //Must run last effect when removed
    }
    //If a action is played, put all the effects in the effect qeue
    else if (_cm->getCard(cid)->getType().compare("ACTION") == 0)
    {
        //std::cout << "Playing a Action" << std::endl;
        _ccm->suspendCard(ccid, cid);
        for (Effect e : _cm->getCard(cid)->getEffects())
            addEffect(e);
        //Execute effects
        resolveEffects();
        _ccm->unSuspendCard(CardContainerID("Trash"));
        //cout << "Action done!" << endl;
    }
    //If Keeper is played, do nothing.
    else if (_cm->getCard(cid)->getType().compare("KEEPER") == 0)
    {
        std::cout << "Playing a Keeper" << std::endl;
        _ccm->moveCard(ccid, CardContainerID(_pm->getCurrentPlayer()->getID().getString() + "_keepers"), cid);

    }
    //Else throw exception
    //Execute effects
    resolveEffects();
}

bool GameLogic::playerDecision(string question, string leftButton, string rightButton)
{
 if(!_gui->isVisible())
     {
        _currentGameState = GameState::QUIT;
     }
    cout << "Decisions has been made" << endl;
      BoardSnapshot snapshot(makeBoardSnapshot());
    return _gui->playerDecision(&snapshot, question,leftButton,rightButton);
}

CardID GameLogic::pickCard(const PlayerID pid, const CardContainerID container)
{
     if (getCurrentGameState() != GameState::CONTINUE) return CardID(0);
     if(!_gui->isVisible())
     {
        _currentGameState = GameState::QUIT;
         return CardID(0);
     }
    BoardSnapshot snapshot(makeBoardSnapshot(pid, container));
    cerr << "GameLogic::pickCard() - Querying GUI for a card." << endl;
    if (_ccm->getSize(container) == 1 && container.val.find("_hand") == string::npos)
    {
        cerr << "GameLogic::pickCard() - Recieved CardID from GUI: " << _ccm->getCards(container).at(0).val << endl;
        return _ccm->getCards(container).at(0);
    }
    else
    {

        CardID id = _gui->pickCard(&snapshot);
        cerr << "GameLogic::pickCard() - Recieved CardID from GUI: " << id.val << endl;
      if(!_gui->isVisible())
     {
        _currentGameState = GameState::QUIT;
         return CardID(0);
     }
        return id;

    }
    //    if(!_gui->isVisible())
    //    {
    //        throw quit_session("The GUI window was closed.");
    //    }

}

PlayerID GameLogic::pickPlayer()
{
     if(!_gui->isVisible())
     {
        _currentGameState = GameState::QUIT;
     }
     cout << "Decisions has been made" << endl;
    BoardSnapshot snapshot(makeBoardSnapshot());
    cerr << "GameLogic::pickPlayer() - Querying GUI for a player." << endl;
    const PlayerID id = _gui->pickPlayer(&snapshot);
    if(!_gui->isVisible())
    {
       _currentGameState = GameState::QUIT;
    }
    cerr << "GameLogic::pickPlayer() - Recieved PlayerID from GUI: " << id.getString() << endl;
    return id;
}

void GameLogic::writeToLog(const string message)
{
    _local_log += message + "\n";
}

void GameLogic::switchPlayer()
{
    if (getCurrentGameState() != GameState::CONTINUE) return;
      if(!_gui->isVisible())
             _currentGameState = GameState::QUIT;
    cout << "Decisions has been made" << endl;
    _log.push_back(make_pair(_pm->getCurrentPlayerID(), _local_log));

    cout << _local_log << endl;
    _local_log = "";
    for (auto i : _log)
    {
        cout << i.first.getString() << "\n" << i.second << endl;
    }
    BoardSnapshot snapshot(makeBoardSnapshot());
    std::cerr << "Entering \"_gui->nextPlayer(&snapshot);\"" << endl;
    _gui->nextPlayer(&snapshot);
    std::cerr << "Returning from \"_gui->nextPlayer(&snapshot);\"" << endl;
}

void GameLogic::drawCard(const PlayerID pid)
{
    if (getCurrentGameState() != GameState::CONTINUE) return;

    _ccm->drawCard(pid.getString() + "_hand");
    _pm->getCurrentPlayer()->incrementTotalCardsDrawn();
}

void GameLogic::checkRules(RuleTrigger rt)
{
    if (getCurrentGameState() != GameState::CONTINUE) return;
    cout << "Check rules" << endl;
    //TODO - waiting for RuleManager to be completed
    vector<Effect> effects = _rm->getTriggeredRules(rt);
    for (unsigned int i = 0; i < effects.size(); i++ )
    {
        addEffect((effects.at(i)));

    }
    resolveEffects();
}


void GameLogic::resolveEffects()
{
    if (getCurrentGameState() != GameState::CONTINUE) return;
    while (!effect_queue.empty())
    {
        executeNextEffect();
    }
}

// const PlayerID GameLogic::getNextPlayer()
// {
//     getPM()->nextPlayer();
//     return getPM()->getCurrentPlayer()->getID();
// }

void GameLogic::executeNextEffect()
{
    if (getCurrentGameState() != GameState::CONTINUE) return;
    Effect e = effect_queue.front();
    effect_queue.pop_front();
    cout << "Effect to Execute: " << e.val << endl;
    executeEffect(e);

}

void GameLogic::executeEffect(const Effect &effect)
{
    if (getCurrentGameState() != GameState::CONTINUE) return;
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
    else if (identifier.compare("ReshuffleContainer") == 0)
    {
        string container;
        ss >> container;
        effect_ReshuffleContainer(container);
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
        for (int i = 0; i < AKeepers_size; i++)
        {
            ss >> tmp;
            AKeepers.push_back(tmp);
        }
        for (int i = 0; i < NKeepers_size; i++)
        {
            ss >> tmp;
            NKeepers.push_back(tmp);
        }
        cout << "Checking Effect BooleanKeeperCheck" << endl;
        effect_BooleanKeeperCheck(AKeepers, NKeepers);
    }
    else if (identifier.compare("ContainerQuantityCheck") == 0)
    {
        string container;
        int quantity;
        ss >> container >> quantity;
        effect_ContainerQuantityCheck(container, quantity);
    }
    else if (identifier.compare("SwapPlayerContainer") == 0)
    {
        cout << "SwapPlayerContainer" << endl << endl << endl;
        string container;
        ss >> container;
        effect_SwapPlayerContainer(container);
    }
    else if (identifier.compare("TrashCards") == 0)
    {
        int quantity;
        ss >> quantity;
        effect_TrashCards(quantity);
    }
    else if (identifier.compare("TrashCardsFromContainer") == 0)
    {
        int quantity;
        string id;
        ss >> quantity >> id;
        effect_TrashCardsFromContainer(quantity, id);
    }
    else if (identifier.compare("ForceRandomPlay") == 0)
    {
        int quantity;
        ss >> quantity;
        effect_ForceRandomPlay(quantity);
    }
    else if (identifier.compare("MoveCards") == 0)
    {
        string ccid1s, ccid2s;
        ss >> ccid1s >> ccid2s;
        effect_MoveContainer(ccid1s, ccid2s);
    }
    else if (identifier.compare("MoveCardsSubtype") == 0)
    {
        string ccid1s, ccid2s, type;
        ss >> ccid1s >> ccid2s >> type;
        effect_MoveCardsSubtype(ccid1s, ccid2s, type);
    }
    else if (identifier.compare("ScramblePlayerContainer") == 0)
    {
        string type;
        ss >> type;
        effect_ScramblePlayerContainer(type);
    }
    else if (identifier.compare("BonusPlayerContainerQuantity") == 0)
    {
        int quantity;
        string container;
        char relation;
        ss >> quantity >> container >> relation;
        effect_bonusPlayerContainerQuantity(quantity, container, relation);
    }
    else if (identifier.compare("BonusPlayerContainerEmpty") == 0)
    {
        int quantity;
        string container;
        ss >> quantity >> container;
        effect_bonusPlayerContainerEmpty(quantity, container);
    }
    else if (identifier.compare("RepeatTurn") == 0)
    {
        effect_RepeatTurn();
    }
    else if (identifier.compare("RotatePlayerContainer") == 0)
    {
        string container;
        ss >> container;
        effect_rotatePlayerContainer(container);
    }
    else if (identifier.compare("DrawAndDistribute") == 0)
    {
        int quantity;
        ss >> quantity;
        effect_DrawAndDistribute(quantity);
    }
    else if (identifier.compare("TakeAndPlayBasedOnSubtype") == 0)
    {
        string container;
        vector<string> subtypes;
        ss >> container;
        string tmp;
        while(ss >> tmp)
        {
            subtypes.push_back(tmp);
        }
        effect_TakeAndPlayBasedOnSubtype(container, subtypes);
    }
    else if (identifier.compare("SetOrder") == 0)
    {
        string direction;
        ss >> direction;
        effect_SetOrder(direction);
    }
    else
    {
        throw std::logic_error("GameLogic::executeEffect() - Undefined Effect: " + identifier);
    }
}

void GameLogic::onNotify(const CardContainerID &cc1, const CardContainerID &cc2 , const CardID &cid,  const Event event)
{
    if (getCurrentGameState() != GameState::CONTINUE) return;
    switch (event)
    {
    case Event::CARD_MOVED:
        checkRules(RuleTrigger::GOAL);

        const CardContainerID trash("Trash");
        const CardContainerID goal("Goal");
        const CardContainerID rules("Rules");
        const CardContainerID suspended ("SuspendedCards");
        cout << "======================" << endl;
        cout << "====   ON NOTIFY  ====" << endl;
        cout << "==" << cc1.val << " " << cc2.val << "==" << endl;
        if (cc2 == goal)
        {
            cout << "ADDING GOAL RULE" << endl;
            addRule(cid, &*(_cm->getCard(cid)->getEffects().begin()), RuleTrigger::GOAL);
        }
        if (cc1 == goal)
        {
            cout << "REMOVE GOAL RULE" << endl;
            removeRule(cid);
        }
        else    if (cc1 == rules)
        {
            cout << "REMOVE RULE RULE" << endl;
            addEffect(*(_cm->getCard(cid)->getEffects().end() - 1));
            executeNextEffect();
        }
        cout << "======================" << endl << endl;
        //if(cc1 == trash)
        //  {
        //     removeRule(cid);
        //     cout << "\n\n Rule Removed" << endl;
        // }

        if (_ccm->getSize(goal) > _rm->getGoalLimmit())
        {
            CardID cid2 = pickCard(_pm->getCurrentPlayer()->getID(), goal);
            _ccm->moveCard(goal, trash, cid2);
            _rm->removeRule(cid2);
        }

        for (Player p : _pm->getPlayers())
        {
            if (p.getID() != _pm->getCurrentPlayer()->getID())
            {
                cout << cc1.val << " " << cc2.val << endl;

                //Hand Limit check
                while (_ccm->getSize(CardContainerID(p.getID().getString() + "_hand")) > _rm->getHandLimit())
                {
                    cout << "Player must discard cards from hand: " << p.getID().getString() << endl;
                    CardContainerID player_hand(p.getID().getString() + "_hand");
                    CardID card_to_trash(0);

                    if (_rm->getHandLimit() == 0)
                    {
                        card_to_trash = _ccm->getRandomCard(player_hand);
                    }
                    else
                    {
                        card_to_trash = pickCard(p.getID(), player_hand);
                    }

                    _ccm->moveCard(player_hand, trash, card_to_trash);
                }

                //Keeper Limit check
                while (_ccm->getSize(CardContainerID(p.getID().getString() + "_keepers")) > _rm->getKeeperLimit())
                {
                    cout << "Player must trash keepers: " << p.getID().getString() << endl;
                    CardContainerID player_keepers(p.getID().getString() + "_keepers");
                    CardID card_to_trash(0);

                    if (_rm->getHandLimit() == 0)
                    {
                        card_to_trash = _ccm->getRandomCard(player_keepers);
                    }
                    else
                    {
                        card_to_trash = pickCard(p.getID(), player_keepers);
                    }

                    _ccm->moveCard(player_keepers, trash, card_to_trash);
                }
            }
        }
        break;
    }
}

GameState GameLogic::getCurrentGameState() const
{
    return _currentGameState;
}

// For use with pickCard() and other functions that require a player and container to be specified.
BoardSnapshot GameLogic::makeBoardSnapshot(const PlayerID active, const CardContainerID target) const
{
    return BoardSnapshot(
               _ccm->getContainers(),
               (int)(_pm->getPlayers().size()),
               _pm->getCurrentPlayerID(),
               active,
               _pm->getNextPlayerID(_rm->getPlayOrder()),
               _pm->getCurrentPlayer()->getCardsPlayed(),
               _rm->getPlay(),
               _rm->getPlayOrder(),
               target,
               _log);
}

// For use with pickPlayer() and other functions that don't need to specify a player and container.
BoardSnapshot GameLogic::makeBoardSnapshot() const
{
    return BoardSnapshot(
               _ccm->getContainers(),
               (int)(_pm->getPlayers().size()),
               _pm->getCurrentPlayerID(),
               _pm->getCurrentPlayerID(),
               _pm->getNextPlayerID(_rm->getPlayOrder()),
               _pm->getCurrentPlayer()->getCardsPlayed(),
               _rm->getPlay(),
               _rm->getPlayOrder(),
               CardContainerID("NULL CONTAINER"),
               _log);
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

    if (_ccm->getSize(CardContainerID("tempA")) == 0)
    {
        ccid = "tempA";
    }
    else if (_ccm->getSize(CardContainerID("tempB")) == 0)
    {
        ccid = "tempB";
    }
    else
    {
        throw std::logic_error("effect_DrawAndPlay() - No empty Temp CardContainer!");
    }

    for (int i = 0 ; i < draw ; i++)
    {
        try
        {
            _ccm->drawCard(CardContainerID(ccid));
        }
        catch (...)
        {
            cout << "GameLogic::effect_DrawAndPlay \tERROR REPORT: Error while drwaing cards from _ccm " << endl;
        }

    }

    for (int i = 0 ; i < play; i++)
    {
        playCard();
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

    if (trigger.compare("PRE_DRAW") == 0)
    {
        rt = RuleTrigger::PRE_DRAW;
    }
    else if (trigger.compare("POST_DRAW") == 0)
    {
        rt = RuleTrigger::POST_DRAW;
    }
    else if (trigger.compare("PRE_PLAY") == 0)
    {
        rt = RuleTrigger::PRE_PLAY;
    }
    else if (trigger.compare("TURN_END") == 0)
    {
        rt = RuleTrigger::TURN_END;
    }
    else if (trigger.compare("GOAL") == 0)
    {
        rt = RuleTrigger::GOAL;
    }
    else
    {
        throw std::logic_error("GameLogic::effect_AddTriggeredRule() - Tried to add TriggeredRule without RuleTrigger");
    }

    addRule(CardID(card_id), &(_cm->getCard(CardID(card_id))->getEffects().at(1)), rt);
}

void GameLogic::effect_RemoveTriggeredRule(int card_id)
{
    _rm->removeRule(CardID(card_id));
}

void GameLogic::effect_ModifyRule(string rule_type, int value)
{
    for (auto i : _ccm->getCards(CardContainerID("Rules")))
    {
        if(_cm->getCard(i)->getEffects().at(0).val.find("AddTriggeredRule") != string::npos )
        {
            if(_cm->getCard(i)->getEffects().at(1).val.find(" "+ rule_type+" ") != string::npos && _cm->getCard(i)->getEffects().at(1).val.find(to_string(value)) == string::npos)
            {
             cout << _cm->getCard(i)->getEffects().at(1).val << " and " << rule_type << endl;
            _ccm->moveCard(CardContainerID("Rules"), CardContainerID("Trash"), i);
             break;
            }
        }

         if(_cm->getCard(i)->getEffects().at(0).val.find("ModifyRule") != string::npos )
        {
            if(_cm->getCard(i)->getEffects().at(0).val.find(rule_type) != string::npos && _cm->getCard(i)->getEffects().at(0).val.find(to_string(value)) == string::npos)
            {
             cout << _cm->getCard(i)->getEffects().at(0).val << " and " << rule_type << endl;
            _ccm->moveCard(CardContainerID("Rules"), CardContainerID("Trash"), i);
             break;
            }
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
            _pm->getCurrentPlayer()->incrementCardsDrawn();
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

    if (_ccm->getSize(CardContainerID("tempA")) == 0)
    {
        ccid = "tempA";
    }
    else if (_ccm->getSize(CardContainerID("tempB")) == 0)
    {
        ccid = "tempB";
    }
    else
    {
        throw std::logic_error("GameLogic::effect_TakeAndPlay() - No available temp container.");
    }

    const CardContainerID temp_container(ccid);
    const CardContainerID target(pickPlayer().getString() + "_hand");
    const PlayerID current_player(_pm->getCurrentPlayer()->getID());

    for (int i = 0 ; (i < take) && (_ccm->getSize(target) > 0); ++i)
    {
        _ccm->moveCard(target, temp_container, _ccm->getRandomCard(target));
    }

    for (int i = 0; i < play; ++i)
    {
        playCard();
    }

    for (int i = 0; i < trash; ++i)
    {
        _ccm->moveCard(temp_container, CardContainerID("Trash"), pickCard(current_player, temp_container));
    }

    CardContainerID player_hand(current_player.getString() + "_hand");

    while (_ccm->getSize(temp_container) > 0)
    {
        _ccm->moveCard(temp_container, player_hand, _ccm->getRandomCard(player_hand));
    }
}

void GameLogic::effect_ReshuffleContainer(string container)
{
    _ccm->containerToStock(CardContainerID(container));
    _ccm->reshuffle();
}

void GameLogic::effect_BooleanKeeperCheck(vector<int> &AKeepers, vector<int> &NKeepers)
{
    bool firstCheck = false;
    PlayerID winningPlayer;
    for (Player i : _pm->getPlayers())
    {
        CardContainerID cpkid(i.getID().getString() + "_keepers");
        unsigned icheck = 0;
        for (int j : AKeepers)
        {
            vector<CardID> vid = _ccm->getCards(cpkid);
            if (find(vid.begin(), vid.end(), CardID(j)) != vid.end())
            {
                cout << "Keeper: " << j << " found in: " << cpkid.val << endl;
                for (CardID id : vid)
                {
                    cout << "Contains: " << id.val << ",";
                }
                cout << endl;
                icheck++;
            }
        }
        cout << "Icheck::\t" << icheck << endl;
        if (icheck == AKeepers.size())
        {
            firstCheck = true;
            winningPlayer = i.getID();
            break;
        }
    }
    cout << "Check one" << firstCheck << endl;
    bool secondCheck = false;
    int icheck = 0;
    for (Player i : _pm->getPlayers())
    {
        CardContainerID cpkid(i.getID().getString() + "_keepers");
        vector<CardID> vid = _ccm->getCards(cpkid);
        for (int j : NKeepers)
        {
            if (find(vid.begin(), vid.end(), CardID(j)) != vid.end())
            {
                cout << "Keeper: " << j << " found in: " << cpkid.val << endl;
                for (CardID id : vid)
                {
                    cout << "Contains: " << id.val << ",";
                }
                cout << endl;
                icheck++;
            }
        }
    }
    if (icheck == 0)
        secondCheck = true;
    cout << "Check two:  " << secondCheck << endl;
    if (firstCheck && secondCheck)
    {
        _currentGameState = GameState::GAME_OVER;
        getPM()->setWinningPlayer(winningPlayer);
        cout << "GAME OVER! WINNING PLAYER: " << winningPlayer.getString() << endl;
    }
}

void GameLogic::effect_ContainerQuantityCheck(string container, int quantity)
{
    string container_type = "";
    
    if (container.compare("keeper") == 0)
    {
        container_type = "_keepers";
    }
    else if (container.compare("hand") == 0)
    {
        container_type = "_hand";
    }
    else
    {
        throw logic_error(container + " is not a valid player container!");
    }

    int max_size = 0;
    int players_with_max = 0;
    PlayerID best_player;

    for (Player p : _pm->getPlayers())
    {
        int container_size = _ccm->getSize(CardContainerID(p.getID().getString() + container_type)) ;
        
        if ( container_size > max_size)
        {
            max_size = container_size;
            players_with_max = 1;
            best_player = p.getID();
        }
        else if ( container_size == max_size)
        {
            players_with_max++;
        }
    }
    if (max_size >= quantity && players_with_max == 1)
    {
        cout << "GAME OVER! WINNING PLAYER: " << best_player.getString() << endl;
        _currentGameState = GameState::GAME_OVER;
        _pm->setWinningPlayer(best_player);
        cout << "GAME OVER! WINNING PLAYER: " << best_player.getString() << endl;
    }
}

void GameLogic::effect_SwapPlayerContainer(string container)
{
    string id1s, id2s;
    if (container.compare("hand") == 0)
    {
        id1s = _pm->getCurrentPlayer()->getID().getString() + "_hand";
        id2s = pickPlayer().getString() + "_hand";
    }
    else if (container.compare("keeper") == 0)
    {
        id1s = _pm->getCurrentPlayer()->getID().getString() + "_keepers";
        id2s = pickPlayer().getString() + "_keepers";
    }
    else
        throw logic_error("no player related container with name: " + container);
    cout << "Picked player: " << id2s << " " << id1s << endl;
    _ccm->swapCards(CardContainerID(id1s), CardContainerID(id2s));

}

void GameLogic::effect_TrashCards(int quantity)
{
    string id1 = pickPlayer().getString() + "_keepers";

    for (int i = 0; i < quantity && _ccm->getSize(CardContainerID(id1)) > 0; i++)
    {
        CardID cid = pickCard(_pm->getCurrentPlayerID(), CardContainerID(id1));
        _ccm->moveCard(CardContainerID(id1), CardContainerID("Trash"), cid);
    }
}

void GameLogic::effect_TrashCardsFromContainer(int quantity, string id)
{
    CardContainerID ccid(id);
    for (int i = 0 ; i < quantity && _ccm->getSize(ccid) > 0; i++)
    {
        CardID cid = pickCard(_pm->getCurrentPlayerID(), ccid);
        _ccm->moveCard(ccid, CardContainerID("Trash"), cid);
    }
}

void GameLogic::effect_ForceRandomPlay(int quantity)
{
    if (getCurrentGameState() != GameState::CONTINUE)
    {
        return;
    }
    else if (_rm->getPlay() <= quantity)
    {
        return;
    }

    CardContainerID player_hand(_pm->getCurrentPlayer()->getID().getString() + "_hand");

    if (_ccm->getSize(player_hand) == 0)
        throw std::logic_error("GameLogic::effect_ForceRandomPlay() - " + player_hand.val + " is empty.");

    vector<CardID> hand(_ccm->getCards(player_hand));

    int seed = time(0);
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> distribution(0, hand.size() - 1);
    unsigned int index = distribution(gen);
    CardID cid = hand.at(index);

    playCardWithID(cid, player_hand);
}

void GameLogic::effect_MoveContainer(string ccid1, string ccid2)
{
    _ccm->moveCards(CardContainerID(ccid1), CardContainerID(ccid2));
}

void GameLogic::effect_MoveCardsSubtype(string ccid1, string ccid2, string type)
{
    for (auto i : _ccm->getCards(ccid1))
    {
        if (_cm->getCard(i)->getSubtype().compare(type) == 0)
        {
            _ccm->moveCard(ccid1, ccid2, i);
        }
    }
}

void GameLogic::effect_ScramblePlayerContainer(string container)
{
    int seed = time(0);
    std::mt19937 gen(seed);
    vector<int> playerContainerCount;
    cout << "GameLogic::effect_ScramblePlayerContainer(): " << "Count Cards and move to system_temp" << endl;
    for (Player p : _pm->getPlayers())
    {
        playerContainerCount.push_back(_ccm->getSize(CardContainerID(p.getID().getString() + "_" + container)));
        _ccm->moveCards(CardContainerID(p.getID().getString() + "_" + container), CardContainerID("system_temp"));
        cout << "Player Size: " << playerContainerCount.at(playerContainerCount.size() - 1) << endl;
    }
    cout << "GameLogic::effect_ScramblePlayerContainer(): " << "Start giving cards to players" << endl;

    for (unsigned int j = 0; j < _pm->getPlayers().size(); j++)
    {
        for (int i = 0 ; i < playerContainerCount.at(j); i++)
        {
            vector<CardID> cards = _ccm->getCards(CardContainerID("system_temp"));
            std::uniform_int_distribution<int> distribution(0, cards.size() - 1);
            unsigned int index = distribution(gen);
            _ccm->moveCard(CardContainerID("system_temp"), CardContainerID(_pm->getPlayers().at(j).getID().getString() + "_" + container), cards.at(index));
        }
    }
    cout << "GameLogic::effect_ScramblePlayerContainer(): " << "End of effect" << endl;
}

void GameLogic::effect_bonusPlayerContainerQuantity(int quantity, string container, char relation)
{
    vector<int> containersSize;
    for (Player p : _pm->getPlayers())
    {
        containersSize.push_back(_ccm->getSize(CardContainerID(p.getID().getString() + "_" + container)));
    }

    int amountOfPlayers = 0;
    int bestPlayer = 0;
    int bestValue = 0;

    if(relation == '<')
    {
        bestValue = 82;
        bestPlayer = 0;
    }

    for (unsigned int i = 0 ; i < containersSize.size(); i++)
    {
        if (relation == '<')
        {
            cout << "Relation check check!" << endl;
            if (containersSize.at(i) < bestValue)
            {
                bestValue = containersSize.at(i);
                bestPlayer = i;
                amountOfPlayers = 0;
            }
            else if (containersSize.at(i) == bestValue)
            {
                amountOfPlayers++;
            }
        }
        else if (relation == '>')
        {
            cout << "Relation check check!" << endl;
            if (containersSize.at(i) > bestValue)
            {
                bestValue = containersSize.at(i);
                bestPlayer = i;
                amountOfPlayers = 0;
            }
            else if (containersSize.at(i) == bestValue)
            {
                amountOfPlayers++;
            }
        }
    }
    cout << "TURNOUT: " << amountOfPlayers << " " <<  bestPlayer << " " <<  bestValue << endl;
    if (amountOfPlayers == 0 && bestPlayer != -1 && _pm->getCurrentPlayerID() == _pm->getPlayers().at(bestPlayer).getID())
    {
        cout << "Player will draw: " << quantity  << "Extra cards" << endl;
        for (int  i = 0; i < quantity; i++)
            _ccm->drawCard(CardContainerID(_pm->getPlayers().at(bestPlayer).getID().getString() + "_hand"));
    }

}

void GameLogic::effect_bonusPlayerContainerEmpty(int quantity, string container)
{
    int containerSize = _ccm->getSize(CardContainerID(_pm->getCurrentPlayer()->getID().getString() + "_" + container));
    if(containerSize == 0)
    {
         for (int  i = 0; i < quantity; i++)
            _ccm->drawCard(CardContainerID(_pm->getCurrentPlayer()->getID().getString() + "_hand"));
    }
}

void GameLogic::effect_rotatePlayerContainer(string container)
{
    bool rotation =    playerDecision("Rotation", "COUNTERCLOCKWISE", "CLOCKWISE");

    vector<vector<CardID>> containers;
    for (unsigned int i = 0; i < _pm->getPlayers().size(); i++)
    {
        CardContainerID ccid(_pm->getPlayers().at(i).getID().getString() + "_" + container);
        containers.push_back(_ccm->getCards(ccid));
    }

    for (unsigned int i = 0; i < _pm->getPlayers().size(); i++)
    {
        int target = i;
        if (rotation)
        {
            target = i - 1;
            if (target == -1)
                target = int(_pm->getPlayers().size() - 1);
        }
        else
        {
            target = i + 1;
            if (target == int(_pm->getPlayers().size()))
                target = 0;
        }
        CardContainerID ccid(_pm->getPlayers().at(i).getID().getString() + "_" + container);
        CardContainerID ccid2(_pm->getPlayers().at(target).getID().getString() + "_" + container);
        for (auto j : containers.at(i))
        {
            _ccm->moveCard(ccid, ccid2, j);
        }
    }
}
void GameLogic::effect_DrawAndDistribute(int quantity)
{
    string ccids;
    if(_ccm->getSize(CardContainerID("tempA")) == 0)
        ccids = "tempA";
    else if(_ccm->getSize(CardContainerID("tempB")) == 0)
        ccids = "tempB";
    else
        throw logic_error("No empty Temp CardContainer!");
    CardContainerID id(ccids);
    for(unsigned int j = 0; j < _pm->getPlayers().size(); j++)
        for(int i = 0; i <  quantity; i++)
        {
           _ccm->drawCard(id);
        }
    for(Player p: _pm->getPlayers())
    {
        for(int j = 0; j <  quantity; j++)
        {
         _ccm->moveCard(id,CardContainerID(p.getID().getString() + "_hand"), pickCard(_pm->getCurrentPlayer()->getID(), id));
        }
    }
}

void GameLogic::effect_RepeatTurn()
{
    _pm->repeatTurn();
}

void GameLogic::effect_SetOrder(string direction)
{
    if (direction.compare("COUNTERCLOCKWISE") == 0)
    {
        if (_pm->getPlayers().size() == 2)
        {
            _ccm->unSuspendCard(CardContainerID("Trash"));
            // I detta utförande är kort-id 55 hårdkodat. Suboptimalt!            
            //getCCM()->moveCard(CardContainerID("Rules"), CardContainerID("Trash"), CardID(55));
            addEffect(Effect{"RepeatTurn"});
        }
        else
        {
            _rm->setPlayOrder(Direction::COUNTERCLOCKWISE);
        }
    
    }
    else if (direction.compare("CLOCKWISE") == 0)
    {
        // Om antalet spelare är två tas regeln omedelbart bort igen, och exit-effekten är effektlös.
        // Spelordningen är iofs meningslös med bara två spelare, så den här kontrollen är kanske inte strikt nödvändig.
        if (!(_pm->getPlayers().size() == 2))
        {
            _rm->setPlayOrder(Direction::CLOCKWISE);
        }
    }
    else
    {
        throw std::logic_error("GameLogic::effect_SetOrder(string direction) - Invalid direction: " + direction);
    }
}

 void GameLogic::effect_TakeAndPlayBasedOnSubtype(string container,vector<string> subtypes)
 {
    bool check = false;
    CardID id(0);
        do
        {
            id = pickCard(_pm->getCurrentPlayer()->getID(), CardContainerID(container));
            for(string s: subtypes)
            {
                check = _cm->getCard(id)->getSubtype().compare(s) == 0;
                break;
            }
        }while(!check);
    playCardWithID(id,CardContainerID(container));
 }


