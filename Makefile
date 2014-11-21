CCC		= g++ -std=c++11
CCFLAGS = -g -Wall -pedantic -c
INCLUDE	= -Iinclude -Iinclude/Effects
#.o files
Card.o: src/Card.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) src/Card.cc
CardContainer.o: src/CardContainer.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) src/CardContainer.cc
CardContainerManager.o: src/CardContainerManager.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) src/CardContainerManager.cc

#TEST .o files
Card_test.o: test/Card_test.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) test/Card_test.cc
CardContainer_test.o: test/CardContainer_test.cc 
	$(CCC) $(CCFLAGS) $(INCLUDE) test/CardContainer_test.cc

#TEST
Card_test: Card_test.o Card.o
	$(CCC) -o Card_test Card_test.o Card.o

CardContainer_test: CardContainer_test.o CardContainer.o Card.o
	$(CCC) -o CardContainer_test CardContainer_test.o CardContainer.o Card.o

##CardID_test: CardID_test.cc 
##	$(CCC) $(CCFLAGS) -o CardID_test CardID_test.cc $(INCLUDE)

##CardManager_test: CardManager_test.cc 
##	$(CCC) $(CCFLAGS) -o CardManager_test CardManager_test.cc $(INCLUDE)

##Deck_test: Deck_test.cc 
##	$(CCC) $(CCFLAGS) -o Deck_test Deck_test.cc $(INCLUDE)

##GameLogic_test: GameLogic_test.cc 
##	$(CCC) $(CCFLAGS) -o GameLogic_test GameLogic_test.cc $(INCLUDE)

##Stock: Stock.cc 
##	$(CCC) $(CCFLAGS) -o Stock Stock.cc $(INCLUDE)

clean:
	@ \rm -rf *.o *.gch