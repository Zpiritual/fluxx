//Author: Johannes
//Changelog:
//==========
//Made copy and move accessable
#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include "Deck.h"
#include "Card.h"
#include "CardID.h"

class CardManager {
public:
//Can only be created with a pointer to a deck object
ContainerID(const Deck* const d) : deck{d}
{}

//Default forbidden
ContainerID() = delete;
CardContainerID(const ContainerID&) = default;
ContainerID (ContainerID&&) = default;

Card* getCard(CardID);

private:
const Deck* const deck;
}