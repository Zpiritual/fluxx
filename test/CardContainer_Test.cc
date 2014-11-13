//Author Martin -- Not complete
#include "CardContainer.h"
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int main()
{
	vector<CardContainer> containers;
	ContainerID id1("Container 1");
	ContainerID id2("HELLO");
	ContainerID id3(id1);
	ContainerID id4(id2);
	id4 = id1;
	CardContainer cc1(id1);
	CardContainer cc2(id2);
	CardContainer cc3(id2);
	CardID cid1(1);
	CardID cid2(2);
	CardID cid3(3);
	cout<< "Adding Card: " << cid1.val << " to: " << cc1.getID().val << endl;
	cc1.addCard(cid1); 
	cout<< "Adding Card: " << cid1.val << " to: " << cc1.getID().val << endl;
	cc1.addCard(cid1);
	cout << "Size: " << cc1.getID().val << " is: " << cc1.getSize() << endl;
	assert(cc1.getSize() == 1);
	cout << "Sanitycheck: Duplicated ids OK" << endl;
	cout<< "Adding Card: " << cid2.val << " to: " << cc1.getID().val << endl;
	cc1.addCard(cid2);
	cout << "Removing Card: " << cid1.val << " from: " << cc1.getID().val << endl;
	cc1.removeCard(cid1);
	cout<< "Adding Card: " << cid1.val << " to: " << cc2.getID().val << endl;
	cc2.addCard(cid1);
	cout<< "Adding Card: " << cid2.val << " to: " << cc2.getID().val << endl;
	cc2.addCard(cid2);
	cout << "Size: " << cc2.getID().val << " is: " << cc2.getSize() << endl;
	return 0;
}