//Author Martin -- Not complete
#include "CardContainer.h"
#include <iostream>
using namespace std;

int main()
{
	CardID * cid = new CardID(5);
	ContainerID* coid = new ContainerID("HELLO");
	CardContainer c1(coid);
	cout << c1.getSize() << endl;
	c1.addCard(cid);
	cout << (c1.getID()->val) << endl;
	cout << c1.getSize() << endl;

	delete cid;
	delete coid;
	return 0;
}