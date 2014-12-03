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
        string container;
        int take, play, trash;
        ss >> container >> take >> play >> trash;
        effect_TakeCard(container, take, play, trash);
    }
    else if (identifier.compare("EmptyContainer") == 0)
    {
        string container;
        ss >> container;
        effect_EmptyContainer(container);
    }
    else
    {
        throw std::logic_error("GameLogic::executeEffect() - Undefined Effect");
    }
}

void effect_DrawAndPlay(int draw, play, trash);
void effect_Redraw();
void effect_AddTriggeredRule(card_id, trigger);
void effect_RemoveTriggeredRule(card_id);
void effect_ModifyRule(rule_type, value);
void effect_TakeAndPlay(string container, int take, play, trash);
void effect_EmptyContainer(string container);

void GameLogic::effect_DrawAndPlay(int draw, play, trash)
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

void GameLogic::effect_AddTriggeredRule(card_id, trigger)
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
    
    addRule(CardID(),card_id &(_cm->getCard(CardID(card_id))->getEffects().at(1)), rt);
}

void GameLogic::effect_RemoveTriggeredRule(card_id)
{
    removeRule(CardID(card_id));
}

void GameLogic::effect_ModifyRule(rule_type, value)
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
        _rm->setHandLimit(p2);
    }
    else if (rule_type.compare("Goal") == 0)
    {
        _rm->setGoalLimmit(p2);
    }
    else if (rule_type.compare("Inflation") == 0)
    {
        _rm->setInflation(p2);
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

void GameLogic::effect_TakeAndPlay(string container, int take, play, trash)
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
    
    if (_ccm->getSize(CardContainerID(p1)) > 0)
        for (int i = 0 ; i < p2; i++)
        {
            _ccm->moveCard(CardContainerID(p1), CardContainerID(ccid), pickCard(_pm->getCurrentPlayer()->getID(), CardContainerID(p1)));
            playCard(_pm->getCurrentPlayer()->getID());
        }
}

void GameLogic::effect_EmptyContainer(string container)
{
    _ccm->clearContainer(CardContainerID(container));
}