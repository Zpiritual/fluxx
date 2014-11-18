#include <"CardContainer.h">

void CardContainerManager::reshuffle()
{
	_stock.shuffle();
}

void CardContainerManager::drawCard(const ContainerID cid)
{
	getContainer(cid).addCard(_stock.pop());
}

void CardContainerManager::moveCard(const ContainerID, const ContainerID, const CardID)
{

}

int CardContainerManager::getSize(const CardcontainerID) const
{

}

vector<CardID> getCards(const ContainerID) const
{

}

CardContainer* const getContainer(const CardContainerID cid)
{
	for (auto i : _containers)
	{
		if (i->getID() == cid)
		{
			return i;
		}
	}

}