#include <iostream>
#include <fstream>
#include "game.h"
using namespace std;

const map<string, vector<int>> Game::propertyRecipes = Game::createPropRecipes();

Game::Game(int seed):
  gen(seed), // seed random gen
  turnCount{0}, // set turn
  gameBoard{make_shared<Board>()}, // TODO initialize board
  fairDice{make_shared<FairDice>(gen)},
  loadedDice{make_shared<LoadedDice>()}
{
  players = {
    make_shared<Player>("Blue", loadedDice, this),
    make_shared<Player>("Red", loadedDice, this),
    make_shared<Player>("Orange", loadedDice, this),
    make_shared<Player>("Yellow", loadedDice, this)
  };

  currentPlayer = players[0];
}

Game::~Game() {}

int Game::getTurnCount() {
  return turnCount;
}

void Game::setTurnCount(int turn) {
  turnCount = turn;
}

shared_ptr<Player> Game::getCurrentPlayer() {
  return currentPlayer;
}

shared_ptr<Player> Game::getPlayer(int index) {
  return players[index];
}

shared_ptr<Player> Game::getPlayer(string colour) {
  for (auto i : players) {
    if (i->getColour() == colour)
      return i;
  }
}

void Game::setPlayer(int index, const PlayerData & pd) {
  weak_ptr<Player> player = getPlayer(index);
  (player.lock())->setResources(pd); // TODO function pending
  //gameBoard->setupProperties(player.lock(), pd); // TODO function pending
}

shared_ptr<Board> Game::getGameBoard() {
  return gameBoard;
}

void Game::setGameBoard(string layout) {
  // gameBoard.setupTiles(layout); // TODO function pending
}

shared_ptr<FairDice> Game::getFairDice() {
  return fairDice;
}

shared_ptr<LoadedDice> Game::getLoadedDice() {
  return loadedDice;
}

int Game::genRand(int min, int max) {
  uniform_int_distribution<> dist{min, max};
  return dist(gen);
}

void Game::listCommands() {
  // uses string literal
  cout << R"(Valid commands:
board
status
residences
build-road <path#>
build-res <housing#>
improve <housing#>
trade <colour> <give> <take>
next
save <file>
help)" << endl;
}

void Game::initGame() {
  // Player initiliazes their properties
}

void Game::resetGame() {}

void Game::saveGame(string file) {}

void Game::loadGame(ifstream & loadFile) {
  int turnCount;
  string loadData;

  if (loadFile) {
    loadFile >> turnCount;
    setTurnCount(turnCount);

    for (int i = 0; i < NUMPLAYERS; i++) {
      getline(loadFile, loadData);
      PlayerData pd(loadData);
      setPlayer(i, pd);
    }

    // getline(loadFile, loadData);
    // getGameBoard()->setLayout(loadData);
    loadFile.close();
  }
}

bool Game::startGame() {
  // initGame();
  // bool win = 0;
  // while (!win)
  // loop through players
  // try
  // win = player->turn()
  // catch errors
  // manage errors

  getPlayer(0)->printStatus();
  getPlayer(0)->buildProperty(5);
  getPlayer(0)->printStatus(); // score = 1
  getPlayer(0)->turn();
  getPlayer(0)->upgradeProperty(5);
  getPlayer(0)->printStatus(); // score = 2
}
