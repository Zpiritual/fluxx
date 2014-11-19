	#include "CardManager.h"

	const Card* const CardManager::getCard(const CardID cid) const { return _deck->getCard(cid); }