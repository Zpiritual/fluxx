CCC		= g++ -std=c++11
CCFLAGS = -g -Wall -pedantic -c
INCLUDE	= -Iinclude

all: clean Card_test CardContainer_test CardID_test CardManager_test Deck_test GameLogic_test DeckParser_test
	@echo
	./Card_test
	@echo
	./CardContainer_test
	@echo
	./CardID_test
	@echo
	./CardManager_test
	@echo
	./Deck_test
	@echo
	./GameLogic_test
	@echo
	./DeckParser_test

%.o: src/%.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) $< -o $@

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

DeckParser_test.o: test/DeckParser_test.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) test/DeckParser_test.cc

RuleManager_test.o: test/RuleManager_test.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) test/RuleManager_test.cc
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

GameLogic_test: GameLogic_test.o GameLogic.o CardManager.o CardContainer.o Player.o Card.o Deck.o CardContainerManager.o PlayerManager.o Stock.o RuleManager.o
	$(CCC) -o GameLogic_test GameLogic_test.o GameLogic.o CardContainer.o CardManager.o Player.o Card.o Deck.o CardContainerManager.o PlayerManager.o Stock.o RuleManager.o

DeckParser_test: DeckParser_test.o DeckParser.o Card.o Deck.o
	$(CCC) -o DeckParser_test DeckParser_test.o DeckParser.o Card.o Deck.o

RuleManager_test: RuleManager_test.o RuleManager.o Card.o TriggeredRule.o
	$(CCC) -o RuleManager_test RuleManager_test.o RuleManager.o Card.o TriggeredRule.o

clean:
	@ \rm -rf *.o *.gch

