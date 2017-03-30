#include <iostream>
#include "game.h"
using namespace std;

const map<string, string> Game::propertyRecipes = Game::createPropRecipes();

Game::Game() {};

Game::~Game() {};

Player * Game::getCurrentPlayer() {};

vector<shared_ptr<Player>> Game::getPlayers() {};

unique_ptr<Board> Game::getGameBoard() {};

unique_ptr<FairDice> Game::getFairDice() {};

unique_ptr<LoadedDice> Game::getLoadedDice() {};

void Game::listCommands() {};

void Game::initGame() {};

void Game::resetGame() {};

void Game::saveGame() {};

void Game::loadGame() {};

// int main() {
//   cout << Game::propertyRecipes.at("Basement") << endl;
// }
