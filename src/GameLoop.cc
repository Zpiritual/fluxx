void GameLoop::playCard(const PlayerID, const CardID);
void GameLoop::drawCards(const PlayerID, const int);

const gameState GameLoop::executePlayerTurn(PlayerID)
{

}

const int GameLoop::getDrawNO() const;
const int GameLoop::getPlayNO() const;
void GameLoop::sendLog(std::string);

SessionData	GameLoop::run()
{
	while (executePlayerTurn() != GAME_OVER)
	{
		//switch screen osv.
	}
}

void GameLoop::switchScreen();
void GameLoop::sendBoardState();
CardID GameLoop::requestInput();