#include "CardManager.h"

CardManager::CardManager(const Deck* const d) : _deck{d}
{}

const Card* CardManager::getCard(const CardID cid) const
{
  return _deck->getCard(cid); 
}
