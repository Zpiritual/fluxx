//Autor Martin
#ifndef CARDCONTAINER_ID
#define CARDCONTAINER_ID
struct CardContainerID
{
int val;
	//Can only be created with a value
	CardContainerID(int val):val{val}
	{}

	//Default, Mode and Copy forbidden
	CardContainerID() = delete;
	CardContainerID(const CardContainerID&) = delete;
	CardContainerID (CardContainerID&&) = delete;

	CardContainerID& operator= (const CardContainerID&) = delete;
	CardContainerID& operator= (CardContainerID&&) = delete;

	//Default Destructor
	~CardContainerID() = default;
};
#endif