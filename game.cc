#include <iostream>
#include "game.h"
using namespace std;

const map<string, vector<int>> Game::propertyRecipes = Game::createPropRecipes();

Game::Game(int seed):
  // gen(seed), // seed random gen
  turnCount{0}, // set turn
  gameBoard{make_shared<Board>()} // TODO initialize board
  // fairDice{make_shared<FairDice>(gen)},
  // loadedDice{make_shared<LoadedDice>()}
{
  players = {
    // make_shared<Player>("Blue", loadedDice, this),
    // make_shared<Player>("Red", loadedDice, this),
    // make_shared<Player>("Orange", loadedDice, this),
    make_shared<Player>("Yellow", this)
  };

  cout << "player made";
  cout << players[0];
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

// void Game::setPlayer(int index, PlayerData pd) {
//   shared_ptr<Player> player = getPlayer(index);
//   player.setup(pd); // TODO function pending
//   gameBoard.setupProps(player, pd); // TODO function pending
// }

shared_ptr<Board> Game::getGameBoard() {
  cout << "gameboard" << endl;

  return gameBoard;
}

void Game::setGameBoard(string layout) {
  // gameBoard.setupTiles(layout); // TODO function pending
}

// shared_ptr<FairDice> Game::getFairDice() {
//   return fairDice;
// }

// shared_ptr<LoadedDice> Game::getLoadedDice() {
//   return loadedDice;
// }

// int Game::genRand(int min, int max) {
//   uniform_int_distribution<> dist{min, max};
//   return dist(gen);
// }

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
  // Board is initialized


}

void Game::resetGame() {}

void Game::saveGame() {}

void Game::loadGame() {}

void Game::startGame() {
  cout << "Player is building..." << endl;
  // getPlayer(0)->printStatus(cout);

  getPlayer(0)->buildProperty(0);

  cout << "poo" << endl;
  getPlayer(0)->printStatus(cout); // score = 1
  getPlayer(0)->turn(cin, cout);
  getPlayer(0)->upgradeProperty(0);
  getPlayer(0)->printStatus(cout); // score = 2
}
