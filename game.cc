#include <iostream>
#include "game.h"
using namespace std;

const map<string, string> Game::propertyRecipes = Game::createPropRecipes();

Game::Game(int seed):
  // gen(seed), // seed random gen
  turnCount{0}, // set turn
  gameBoard{} // TODO initialize board
  // fairDice{make_shared<FairDice>(gen)},
  // loadedDice{make_shared<LoadedDice>()}
{
  players = {
    // make_shared<Player>("Blue", loadedDice, this),
    // make_shared<Player>("Red", loadedDice, this),
    // make_shared<Player>("Orange", loadedDice, this),
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

// void Game::setPlayer(int index, PlayerData pd) {
//   shared_ptr<Player> player = getPlayer(index);
//   player.setup(pd); // TODO function pending
//   gameBoard.setupProps(player, pd); // TODO function pending
// }

shared_ptr<Board> Game::getGameBoard() {
  return gameBoard;
}

void Game::setGameBoard(string layout) {
  gameBoard.setupTiles(layout); // TODO function pending
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



}
