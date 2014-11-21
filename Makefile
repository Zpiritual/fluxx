CCC		= g++ -std=c++11
CCFLAGS = -g -Wall -pedantic -c
INCLUDE	= -Iinclude -Iinclude/Effects
##DEPS 	= CardID.h Card.h CardContainer.h CardContainerManager.h CardContainerID.h CardManager.h Deck.h GameLogic.h Player.h PlayerID.h PlayerManager.h RuleManager.h SessionData.h Stock.h TirggeredRule.h Effect.h Draw.h BoardSnapshot.h
##%.o: %.cc
##	$(CCC) $(CCFLAGS) $(INCLUDE)  src/$<
%.o: %.cc
	echo Compiling $<...
	$(CCC) $(CCFLAGS) $(INCLUDE) $@

##.o files##
Card.o: src/Card.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) src/Card.cc
CardContainer.o: src/CardContainer.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) src/CardContainer.cc
CardContainerManager.o: src/CardContainerManager.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) src/CardContainerManager.cc
CardManager.o: src/CardManager.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) src/CardManager.cc
Deck.o: src/Deck.cc 
	$(CCC) $(CCFLAGS) $(INCLUDE) src/Deck.cc
Player.o: src/Player.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) src/Player.cc
PlayerManager.o: src/PlayerManager.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) src/PlayerManager.cc
GameLogic.o: src/GameLogic.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) src/GameLogic.cc
Stock.o: src/Stock.cc 
	$(CCC) $(CCFLAGS) $(INCLUDE) src/Stock.cc

##TEST .o files##
Card_test.o: test/Card_test.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) test/Card_test.cc
CardContainer_test.o: test/CardContainer_test.cc 
	$(CCC) $(CCFLAGS) $(INCLUDE) test/CardContainer_test.cc
CardID_test.o: test/CardID_test.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) test/CardID_test.cc
CardManager_test.o: test/CardManager_test.cc 
	$(CCC) $(CCFLAGS) $(INCLUDE) test/CardManager_test.cc
Deck_test.o: test/Deck_test.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) test/Deck_test.cc
GameLogic_test.o: test/GameLogic_test.cc  
	$(CCC) $(CCFLAGS) $(INCLUDE) test/GameLogic_test.cc

##TEST###
Card_test: Card_test.o Card.o
	$(CCC) -o Card_test Card_test.o Card.o

CardContainer_test: CardContainer_test.o CardContainer.o Card.o
	$(CCC) -o CardContainer_test CardContainer_test.o CardContainer.o Card.o

CardID_test: CardID_test.o 
	$(CCC) -o CardID_test CardID_test.o

CardManager_test: CardManager_test.o Deck.o Card.o
	$(CCC) -o CardManager_test CardManager_test.o Deck.o Card.o

Deck_test: Deck_test.o Deck.o Card.o
	$(CCC) -o Deck_test Deck_test.o Deck.o Card.o

GameLogic_test: GameLogic_test.o GameLogic.o CardManager.o CardContainer.o Player.o Card.o Deck.o CardContainerManager.o PlayerManager.o Stock.o
	$(CCC) -o GameLogic_test GameLogic_test.o GameLogic.o CardContainer.o CardManager.o Player.o Card.o Deck.o CardContainerManager.o PlayerManager.o Stock.o

clean:
	@ \rm -rf *.o *.gch

