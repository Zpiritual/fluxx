//Author Martin -- Not complete
#include "CardContainer.h"
#include <iostream>
using namespace std;

int main()
{
	vector<CardContainer> containers;
	for(int i = 1; i <= 5; i++)
	{
		CardContainer c("Cotnainer " + i);
		containers.push_back(c);
	}
	CardContainer c1(coid);


	return 0;
}