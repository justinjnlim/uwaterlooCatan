#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "property.h"

class Player: public std::enable_shared_from_this<Player> {
  std::string colour;
  int numPoints;
  std::map<int, std::shared_ptr<Property>> properties;
  std::map<int, std::shared_ptr<Road>> roads;
  std::vector<ResourceType> resources;
  Dice * diceChosen;
  Game * g;

public:
  Player(string colour, Game * g);
  void addResource(ResourceType r, int qty);
  void buildProperty(int id);
  void upgradeProperty(int id);
  std::string printStatus(std::iostream &out);
  void turn(istream &in, ostream &out);
};

#endif
