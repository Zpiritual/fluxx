#include <"CardContainer.h">

void CardContainerManager::reshuffle()
{
	_stock.shuffle();
}

void CardContainerManager::drawCard(const CardContainerID cid)
{
	getContainer(ccid).addCard(_stock.pop());
}

void CardContainerManager::moveCard(const CardContainerID from, const CardContainerID to, const CardID card)
{
	getContainer(from)->removeCard(card);
	getContainer(to)->addCard(card);
}

int CardContainerManager::getSize(const CardContainerID container) const
{
	getContainer(container)->getSize();
}

vector<CardID> getCards(const CardContainerID container) const
{
	return getContainer(container)->getCards();
}

CardContainer* const getContainer(const CardContainerID container)
{
	return _containers.at(container);
}