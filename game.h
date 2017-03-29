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
  std::vector<std::shared_ptr<Player>> players; // TODO initialize player (know signature)
  std::vector<std::shared_ptr<Dice>> gameDices;

 public:
  static const std::map<std::string, std::string> propertyRecipes;
  static std::map<std::string, std::string> createPropRecipes();

  Game();
  ~Game();
  Player * getCurrentPlayer();
  std::unique_ptr<Board> getGameBoard();
  void listCommands();
  void initGame();
  void resetGame();
  void saveGame();
  void loadGame();
};

#endif
