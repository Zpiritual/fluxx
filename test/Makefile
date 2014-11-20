CCC		= g++ -std=c++11
CCFLAGS = -g -Wall -pedantic
INCLUDE	= -I../include -I../include/Effects -I../src

Card_test: Card_test.cc 
	$(CCC) $(CCFLAGS) -o Card_test Card_test.cc $(INCLUDE)

CardContainer_test: CardContainer_test.cc 
	$(CCC) $(CCFLAGS) -o CardContainer_test CardContainer_test.cc $(INCLUDE)

CardID_test: CardID_test.cc 
	$(CCC) $(CCFLAGS) -o CardID_test CardID_test.cc $(INCLUDE)

CardManager_test: CardManager_test.cc 
	$(CCC) $(CCFLAGS) -o CardManager_test CardManager_test.cc $(INCLUDE)

Deck_test: Deck_test.cc 
	$(CCC) $(CCFLAGS) -o Deck_test Deck_test.cc $(INCLUDE)

GameLogic_test: GameLogic_test.cc 
	$(CCC) $(CCFLAGS) -o GameLogic_test GameLogic_test.cc $(INCLUDE)

Stock: Stock.cc 
	$(CCC) $(CCFLAGS) -o Stock Stock.cc $(INCLUDE)

clean:
	@ \rm -rf *.o *.gch