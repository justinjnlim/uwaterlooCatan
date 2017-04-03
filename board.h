#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>
#include <map>
#include <memory>
#include "resources.h"
/* #include "property.h" */
#include "subject.h"
/* #include "tile.h" */
/* #include "player.h" */
class Road;
class Property;
class Player;
class Tile;
class Game;
class TextDisplay;

class Board : public Subject {

  /* std::map<int,std::shared_ptr<Road>> roads; */
  //std::map<int,std::shared_ptr<Property>> properties;
  //std::map<int,std::vector<std::shared_ptr<Tile>>> tiles;
  std::vector<std::shared_ptr<Road>> roads;
  std::vector<std::shared_ptr<Property>> properties;
  std::vector<std::shared_ptr<Tile>> tiles;
  int diceValue;

  std::shared_ptr<TextDisplay> td;

  //used for random Generation
  std::vector<int> resourceDistribution = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,4,4,4,5};
  std::vector<int> diceDistribution = {2,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11,12};
  Game * g;
  // private

  void linkAssets();
  void linkRoads_Properties();
  void linkTiles_Properties();
  void linkTiles_Roads();
  void removeGoose();

 public:

  Board(Game * g);

  std::shared_ptr<Property> buildProperty(int id, std::shared_ptr<Player> player);

  void getDiceRoll(int diceRoll);

  std::string save();
  void printTiles();
  void printBoard();
  Info getInfo() const override;
  void setupTiles(std::string layout);
  void randomizeTiles();
  bool addGoose(int id);

  friend std::ostream &operator<<(std::ostream &out, const Board& b);
  std::string whoLivesOnTile(int address, std::string colour);
};

#endif
