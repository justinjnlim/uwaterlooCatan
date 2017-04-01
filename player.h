#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
/* #include "property.h" */
#include "resources.h"
/* #include "game.h" */
class Property;
class Game;
class Dice;

class Player: public std::enable_shared_from_this<Player> {
  std::string colour;
  int numPoints;
  std::map<int, std::shared_ptr<Property>> properties;
  /* std::map<int, std::shared_ptr<Road>> roads; */
  std::vector<int> resources;
  std::vector<int> changeInResources;
  std::shared_ptr<Dice> diceChosen;
  Game * g;

public:
  Player(std::string colour, std::shared_ptr<Dice> diceChosen, Game * g);
  void addResource(ResourceType r, int qty);
  bool buildProperty(int id);
  bool upgradeProperty(int id);
  void turn(std::istream &in, std::ostream &out);
  void printStatus(std::ostream &out);

  // SETTERS/GETTERS
  // void setPoints(int p);
};

#endif
