#ifndef _GAME_H_
#define _GAME_H_
#include <memory>
#include <string>
#include <vector>
#include <map>
#include "player.h"
#include "loaded_dice.h"
#include "fair_dice.h"
#include "board.h"
#include "player_data.h"

class Game {
 private:
  Player * currentPlayer;
  std::unique_ptr<Board> gameBoard;
  std::unique_ptr<FairDice> fairDice;
  std::unique_ptr<LoadedDice> loadedDice;
  std::vector<std::shared_ptr<Player>> players; // TODO initialize player (know signature)

 public:
  static const std::map<std::string, std::string> propertyRecipes;
  static std::map<std::string, std::string> createPropRecipes() {
    std::map<std::string, std::string> m;
    m["Basement"] = "Brick 1 Energy 1 Glass 1 Wifi 1";
    m["House"] = "Glass 2 Heat 3";
    m["Tower"] = "Brick 3 Energy 2 Glass 2 Wifi 1 Heat 2";
    return m;
  }

  Game();
  ~Game();
  Player * getCurrentPlayer();
  std::vector<std::shared_ptr<Player>> getPlayers();
  std::unique_ptr<Board> getGameBoard();
  std::unique_ptr<FairDice> getFairDice();
  std::unique_ptr<LoadedDice> getLoadedDice();

  void listCommands();
  void initGame();
  void resetGame();
  void saveGame();
  void loadGame();
};

#endif
