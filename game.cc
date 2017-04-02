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

// TODO set current player

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

// void Game::setPlayer(int index, const PlayerData & pd) {
//   weak_ptr<Player> player = getPlayer(index);
//   (player.lock())->setResources(pd); // TODO function pending
//   //gameBoard->setupProperties(player.lock(), pd); // TODO function pending
// }

void Game::setPlayer(weak_ptr<Player> player, const PlayerData & pd) {
  (player.lock())->setResources(pd);
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

void Game::init() {
  // Player initiliazes their properties

  for (auto i = players.begin(); i != players.end(); i++) {
    i->initTurn();
  }

  for (auto i = players.rbegin(); i != players.rend(); i++) {
    i->initTurn();
  }

  // board->print();
}

void Game::save(string file) {
  string path = "provided_files/" + file;
  ofstream saveFile(path);

  saveFile << getTurnCount() << endl;

  for (shared_ptr<Player> p : players) {
    saveFile << p->save() << endl;
  }

  // board->save();
  saveFile.close();
}

void Game::load(ifstream & loadFile) {
  int turnCount;
  string loadData;

  if (loadFile) {
    getline(loadFile, loadData);
    turnCount = stoi(loadData);
    setTurnCount(turnCount);

    for (shared_ptr<Player> p : players) {
      getline(loadFile, loadData);
      PlayerData pd(loadData);
      setPlayer(p, pd);
    }

    // getline(loadFile, loadData);
    // board->setGameBoard(loadData)
    // loadFile.close();
  }
}

bool Game::start() {
  // initGame();
  // bool win = 0;
  // while (!win)
  // playerTurn = getTurnCount % NUMPLAYER
  // player = getPlayer(playerTurn)
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
