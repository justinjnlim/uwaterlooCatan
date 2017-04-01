#ifndef _GAME_H_
#define _GAME_H_
#include <memory>
#include <string>
#include <vector>
#include <random>
#include <map>
#include "player.h"
/* #include "loaded_dice.h" */
/* #include "fair_dice.h" */
#include "board.h"
class PlayerData;

class Game {
 private:
  /* std::mt19937 gen; */
  int turnCount;
  std::shared_ptr<Player> currentPlayer;
  std::shared_ptr<Board> gameBoard;
  /* std::shared_ptr<FairDice> fairDice; */
  /* std::shared_ptr<LoadedDice> loadedDice; */
  std::vector<std::shared_ptr<Player>> players; // TODO initialize player (know signature)

 public:
  static const std::map<std::string, std::vector<int>> propertyRecipes;
  static std::map<std::string, std::vector<int>> createPropRecipes() {
    std::map<std::string, std::string> m;
    m["Basement"] = {1, 1, 1, 0, 1}; // "Brick 1 Energy 1 Glass 1 Wifi 1"
    m["House"] = {0, 0, 2, 3, 0}; // "Glass 2 Heat 3"
    m["Tower"] = {3, 2, 2, 2, 1}; // "Brick 3 Energy 2 Glass 2 Wifi 1 Heat 2"
    return m;
  }

  Game(int seed = 1);
  ~Game();
  int getTurnCount();
  void setTurnCount(int turn);

  std::shared_ptr<Player> getCurrentPlayer();
  std::shared_ptr<Player> getPlayer(int index);
  /* void setPlayer(int index, PlayerData pd); */

  std::shared_ptr<Board> getGameBoard();
  void setGameBoard(std::string layout);

  /* std::shared_ptr<FairDice> getFairDice(); */
  /* std::shared_ptr<LoadedDice> getLoadedDice(); */

  /* int genRand(int min, int max); */
  void listCommands();
  void initGame();
  void resetGame();
  void saveGame();
  void loadGame();
  void startGame();
};

#endif
