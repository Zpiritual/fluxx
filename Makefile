CCC		= g++ -std=c++11
CCFLAGS = -g -Wall -pedantic -c
INCLUDE	= -Iinclude

all: Card_test CardContainer_test CardID_test CardManager_test Deck_test GameLogic_test GameLoop_test DeckParser_test
	@echo
	./bin/Card_test
	@echo
	./bin/CardContainer_test
	@echo
	./bin/CardID_test
	@echo
	./bin/CardManager_test
	@echo
	./bin/Deck_test
	@echo
	./bin/GameLogic_test
	@echo
	./bin/GameLoop_test
	@echo
	./bin/DeckParser_test

new: clean all
	

bin/%.o: src/%.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) $< -o $@

##TEST .o files##
bin/Card_test.o: test/Card_test.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) -o bin/Card_test.o test/Card_test.cc

bin/CardContainer_test.o: test/CardContainer_test.cc 
	$(CCC) $(CCFLAGS) $(INCLUDE) -o bin/CardContainer_test.o test/CardContainer_test.cc

bin/CardID_test.o: test/CardID_test.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) -o bin/CardID_test.o test/CardID_test.cc

bin/CardManager_test.o: test/CardManager_test.cc 
	$(CCC) $(CCFLAGS) $(INCLUDE) -o bin/CardManager_test.o test/CardManager_test.cc

bin/Deck_test.o: test/Deck_test.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) -o bin/Deck_test.o test/Deck_test.cc

bin/GameLogic_test.o: test/GameLogic_test.cc  
	$(CCC) $(CCFLAGS) $(INCLUDE) -o bin/GameLogic_test.o test/GameLogic_test.cc

bin/DeckParser_test.o: test/DeckParser_test.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) -o bin/DeckParser_test.o test/DeckParser_test.cc

bin/GameLoop_test.o: test/GameLoop_test.cc	
	$(CCC) $(CCFLAGS) $(INCLUDE) -o bin/GameLoop_test.o test/GameLoop_test.cc

bin/RuleManager_test.o: test/RuleManager_test.cc
	$(CCC) $(CCFLAGS) $(INCLUDE) -o bin/RuleManager_test.o test/RuleManager_test.cc
##TEST###
Card_test: bin/Card_test.o bin/Card.o
	$(CCC) -o bin/Card_test bin/Card_test.o bin/Card.o

CardContainer_test: bin/CardContainer_test.o bin/CardContainer.o bin/Card.o
	$(CCC) -o bin/CardContainer_test bin/CardContainer_test.o bin/CardContainer.o bin/Card.o

CardID_test: bin/CardID_test.o 
	$(CCC) -o bin/CardID_test bin/CardID_test.o

CardManager_test: bin/CardManager_test.o bin/Deck.o bin/Card.o
	$(CCC) -o bin/CardManager_test bin/CardManager_test.o bin/Deck.o bin/Card.o

Deck_test: bin/Deck_test.o bin/Deck.o bin/Card.o
	$(CCC) -o bin/Deck_test bin/Deck_test.o bin/Deck.o bin/Card.o

GameLogic_test: bin/GameLogic_test.o bin/GameLogic.o bin/CardManager.o bin/CardContainer.o bin/Player.o bin/Card.o bin/Deck.o bin/CardContainerManager.o bin/PlayerManager.o bin/Stock.o bin/RuleManager.o bin/TriggeredRule.o
	$(CCC) -o bin/GameLogic_test bin/GameLogic_test.o bin/GameLogic.o bin/CardContainer.o bin/CardManager.o bin/Player.o bin/Card.o bin/Deck.o bin/CardContainerManager.o bin/PlayerManager.o bin/Stock.o bin/RuleManager.o bin/TriggeredRule.o

DeckParser_test: bin/DeckParser_test.o bin/DeckParser.o bin/Card.o bin/Deck.o
	$(CCC) -o bin/DeckParser_test bin/DeckParser_test.o bin/DeckParser.o bin/Card.o bin/Deck.o

GameLoop_test: bin/GameLoop_test.o bin/GameLoop.o bin/GameLogic.o bin/CardManager.o bin/CardContainer.o bin/Player.o bin/Card.o bin/Deck.o bin/CardContainerManager.o bin/PlayerManager.o bin/Stock.o bin/RuleManager.o bin/TriggeredRule.o
	$(CCC) -o bin/GameLoop_test bin/GameLoop_test.o bin/GameLoop.o bin/GameLogic.o bin/CardContainer.o bin/CardManager.o bin/Player.o bin/Card.o bin/Deck.o bin/CardContainerManager.o bin/PlayerManager.o bin/Stock.o bin/RuleManager.o bin/TriggeredRule.o

RuleManager_test: bin/RuleManager_test.o bin/RuleManager.o bin/Card.o bin/TriggeredRule.o
	$(CCC) -o bin/RuleManager_test bin/RuleManager_test.o bin/RuleManager.o bin/Card.o bin/TriggeredRule.o

clean:
	@ \rm -rf bin/*.o bin/*.gch bin/*.exe

