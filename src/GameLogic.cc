#include "GameLogic.h"
#include <iostream>
#include <sstream>
#include <string>

GameLogic::GameLogic(const Gui * gui, const Deck * deck, const int players)
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

    //Spela det givna kortet.
    //if a Goal card is placed check if there is room for it
    //if not ask what card to replace
    if (_cm->getCard(cid)->getType() == "GOAL")
    {
        if (_ccm->getSize(CardContainerID("Goal")) > _rm->getGoalLimmit())
        {
            _ccm->moveCard(CardContainerID("Goal"), CardContainerID("Trash"), pickCard(_pm->getCurrentPlayer()->getID(), CardContainerID("Goal")));
        }
        _ccm->moveCard(ccid, CardContainerID("Goal"), cid);
        //Add effect
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

        for (Effect e : _cm->getCard(cid)->getEffects())
            addEffect(e);
        //Execute effects
        resolveEffects();
        _ccm->moveCard(ccid, CardContainerID("Trash"), cid);
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

const CardID GameLogic::pickCard(const PlayerID pid, const CardContainerID) const
{
	//GUI pickCard
}

const PlayerID GameLogic::pickPlayer() const
{
	//GUI pickPlayer
}

void GameLogic::switchPlayer()
{
	//GUI Switch player
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
//Private Effect function
void GameLogic::executeEffect(const Effect &effect)
{
    std::stringstream ss(effect.val);
    string identifier;
    ss >> identifier;
    if (identifier.compare("DrawCard") == 0)
    {
        cout << "DrawCard Triggered" << endl;
        int p1, p2, p3;
        ss >> p1 >> p2 >> p3;
        cout << p1 << " " << p2 << " "  << p3 << endl;
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
            throw std::logic_error("No empty Temp CardCotnainer!");
        cout << "Effect puts cards in: " << ccid << endl;
        for (int i = 0 ; i < p1 ; i++)
        {
            _ccm->drawCard(CardContainerID(ccid));
        }

        for (int i = 0 ; i < p2; i++)
        {
            playCard(_pm->getCurrentPlayer()->getID());
        }
        cout << "trash cards: " << endl;
        for (int i = 0 ; i < p3; i++)
        {
            _ccm->moveCard(CardContainerID(ccid), CardContainerID("Trash"), pickCard(_pm->getCurrentPlayer()->getID(), CardContainerID(ccid)));
        }

        for (CardID cid : _ccm->getCards(CardContainerID(ccid)))
        {
            _ccm->moveCard(CardContainerID(ccid), CardContainerID(_pm->getCurrentPlayer()->getID().getString() + "_hand"), cid);
        }

        cout << "Size of: " << ccid << " " <<  getCCM()->getSize(CardContainerID("tempA")) << endl;
        //std::cout << "Executed: " << effect.val << std::endl;
    }
    else if (identifier.compare("Redraw") == 0)
    {
        cout << "Discard and Draw" << endl;
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
        cout << "Size of Hand: " << _ccm->getSize(CardContainerID(_pm->getCurrentPlayer()->getID().getString() + "_hand")) << " Size of Trash: " << _ccm->getSize(CardContainerID("Trash")) << endl;

    }
    else if (identifier.compare("AddTriggeredRule") == 0)
    {
        int p1;
        string p2;
        ss >> p1 >> p2;
        RuleTrigger rt;
        if (identifier.compare("PRE_DRAW"))
            rt = RuleTrigger::PRE_DRAW;
        else if (identifier.compare("POST_DRAW"))
            rt = RuleTrigger::POST_DRAW;
        else if (identifier.compare("PRE_PLAY"))
            rt = RuleTrigger::PRE_PLAY;
        else if (identifier.compare("TURN_END"))
            rt = RuleTrigger::TURN_END;
        else
            throw std::logic_error("Tried to add TriggeredRule without RuleTrigger");
        addRule(CardID(p1), &(_cm->getCard(CardID(p1))->getEffects().at(1)), rt);
    }
    else if (identifier.compare("RemoveTriggeredRule") == 0)
    {
        int p1;
        ss >> p1;
        removeRule(CardID(p1));
    }
    else if (identifier.compare("GameLimitModifier") == 0)
    {
        string p1;
        int p2;
        ss >> p1 >> p2;
        cout << "conflict: " << p1 << endl;
        for (auto i : _ccm->getCards(CardContainerID("Rules")))
        {
            if (_cm->getCard(i)->getSubtype().compare(p1) == 0)
                removeRule(i);
        }
        if (p1.compare("Play") == 0)
            _rm->setPlay(p2);
        else if (p1.compare("Draw") == 0)
        {
            _rm->setDraw(p2);
            while (_pm->getCurrentPlayer()->getCardsDrawn() < _rm->getDraw())
            {
                drawCard(_pm->getCurrentPlayer()->getID());
            }
        }
        else if (p1.compare("Keeper") == 0)
            _rm->setKeeperLimit(p2);
        else if (p1.compare("Hand") == 0)
            _rm->setHandLimit(p2);
        else if (p1.compare("Goal") == 0)
            _rm->setGoalLimmit(p2);
        else if (p1.compare("Inflation") == 0)
            _rm->setInflation(p2);
        else if (p1.compare("PlayOrder") == 0)
            if (p2 == 1)
                _rm->setPlayOrder(Direction::CLOCKWISE);
            else
                _rm->setPlayOrder(Direction::COUNTERCLOCKWISE);
        else
            throw std::logic_error("GameLimitModifier missing GameLimit Parameter");
    }
    else if (identifier.compare("TakeCard") == 0)
    {
        string p1;
        int p2, p3;
        ss >> p1 >> p2 >> p3;
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
            throw std::logic_error("No empty temp container to put card in!");
        if (_ccm->getSize(CardContainerID(p1)) > 0)
            for (int i = 0 ; i < p2; i++)
            {
                _ccm->moveCard(CardContainerID(p1), CardContainerID(ccid), pickCard(_pm->getCurrentPlayer()->getID(), CardContainerID(p1)));
                playCard(_pm->getCurrentPlayer()->getID());
            }
    }
    else if (identifier.compare("EmptyContainer") == 0)
    {
        string p1;
        ss >> p1;
        _ccm->clearContainer(CardContainerID(p1));
    }
    else
        throw std::logic_error("Undefined Effect");
}

void GameLogic::onNotify(const CardContainerID &cc1, const CardContainerID &cc2 , const Event event)
{
    switch (event)
    {
    case Event::CARD_MOVED:

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
                while (_ccm->getSize(CardContainerID(p.getID().getString() + "_keepers")) > _rm->getKepperLimit())
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
