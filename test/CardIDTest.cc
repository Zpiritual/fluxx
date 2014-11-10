#include "CardID.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	CardID c1(1);
	cout << "Running CardID test..." << endl;
	assert(c1.val == 1);
	cout << "Value check OK" << endl;
	return 0;
}