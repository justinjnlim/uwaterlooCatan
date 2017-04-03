#include <iostream>
#include <fstream>
#include <stdexcept>
#include "game.h"
using namespace std;

const map<string, vector<int>> Game::propertyRecipes = Game::createPropRecipes();

Game::Game(int seed):
  gen(seed), // seed random gen
  turnCount{0}, // set turn
  gameBoard{make_shared<Board>(this)}, // TODO initialize board
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

mt19937 Game::getRandEng() {
  return gen;
}

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

void Game::setPlayer(shared_ptr<Player> player, const PlayerData & pd) {
  player->setResources(pd);
  gameBoard->setupAssets(player, pd); // TODO function pending
}

shared_ptr<Board> Game::getGameBoard() {
  return gameBoard;
}

void Game::setGameBoard(ifstream & loadFile) {
  string layout;

  if (loadFile) {
    getline(loadFile, layout);
    gameBoard->setupTiles(layout);
  } else {
    throw runtime_error("Could not open file");
  }
}

void Game::setGameBoard() {
  gameBoard->randomizeTiles();
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

void Game::listRecipes() {
  cout << R"(Recipes:
Basement - [ 1 x Brick, 1 x Energy, 1 x Glass, 1 x Wifi ]
House - [ 2 x Glass,  3 x Heat ]
Tower - [ 3 x Brick,  2 x Energy,  2 x Glass,  2 x Heat,  1 x Wifi ]
Road - [ 1 x Heat,  1 x Wifi ])" << endl;
}

void Game::listCommands() {
  cout << R"(Valid commands:
board
status
residences
recipes
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
    (*i)->initTurn();
  }

  for (auto i = players.rbegin(); i != players.rend(); i++) {
    (*i)->initTurn();
  }

  cout << *(gameBoard.get());
}

void Game::save(string file) {
  string path = file;
  ofstream saveFile(path);

  saveFile << getTurnCount() << endl;

  for (shared_ptr<Player> p : players) {
    saveFile << p->save() << endl;
  }

  saveFile << gameBoard->save() << endl;
  saveFile.close();
}

void Game::saveLayout(string file) {
  string path = file;
  ofstream layoutFile(path);

  layoutFile << gameBoard->save() << endl;
  layoutFile.close();
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

    getline(loadFile, loadData);
    gameBoard->setupTiles(loadData);
    loadFile.close();
  } else {
    throw runtime_error("Could not open file");
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

  cin.exceptions(istream::failbit|istream::eofbit|istream::badbit);

  int turn;
  weak_ptr<Player> player;
  bool win = 0;
  while (!win) {
    turn = getTurnCount() % NUMPLAYERS;
    player = getPlayer(turn);

    try {
      win = (player.lock())->turn();
      turnCount++;
    } catch (istream::failure & e) {
      if (cin.eof()) {
        cout << "Game terminating due to EOF. Saving..." << endl;
        save("backup.sv");
        cout << "Done." << endl;
      }
      return 0;
    }
  }

  // Game won
  string response;
  cout << (player.lock())->getColour() << " has won the game!" << endl;
  cout << "Would you like to play again? [Yes/No]" << endl;
  cout << "> ";
  while (cin >> response) {
    if (response == "Yes" || response == "Y" || response == "y")
      return 1;
    else if (response == "No" || response == "N" || response == "n")
      return 0;
    else {
      cout << "Invalid option. Would you like to play again? [Yes/No]" << endl;
      cout << "> ";
    }
  }
}
