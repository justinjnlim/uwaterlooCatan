#ifndef _BOARD_H_
#define _BOARD_H_
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

class Board : public Subject {

  /* std::map<int,std::shared_ptr<Road>> roads; */
  //std::map<int,std::shared_ptr<Property>> properties;
  //std::map<int,std::vector<std::shared_ptr<Tile>>> tiles;
  std::vector<std::shared_ptr<Road>> roads;
  std::vector<std::shared_ptr<Property>> properties;
  std::vector<std::shared_ptr<Tile>> tiles;
  int diceValue;

  //used for random Generation
  std::vector<int> resourceDistribution = {4,4,4,3,3,1};
  std::vector<int> diceDistrbution = {2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12};
  Game * g;
  // private
  ResourceType getRandomResource();

  void linkAssets();
  void linkRoads_Properties();
  void linkTiles_Properties();
  void linkTiles_Roads();

 public:

  Board(Game * g);

  std::shared_ptr<Property> buildProperty(int id, std::shared_ptr<Player> player);

  void getDiceRoll(int diceRoll);

  void save();

  Info getInfo() const override;
  void setupTiles(std::string layout);
  void randomizeTiles();


};

#endif
