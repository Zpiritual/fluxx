#include "CardManager.h"

CardManager::CardManager(const Deck* const d) : _deck{d}
{}
const Card* const CardManager::getCard(const CardID cid) const
{
  return _deck->getCard(cid); 
}