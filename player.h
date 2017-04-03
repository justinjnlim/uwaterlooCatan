#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include "resources.h"
#include "player_data.h"
class Property;
class Game;
class Dice;
class Road;

class Player: public std::enable_shared_from_this<Player> {
  std::string colour;
  int numPoints;
  std::map<int, std::weak_ptr<Property>> properties;
  std::map<int, std::weak_ptr<Road>> roads;
  std::vector<int> resources;
  std::vector<int> changeInResources;
  std::weak_ptr<Dice> diceChosen;
  Game * g;

public:
  Player(std::string colour, std::weak_ptr<Dice> diceChosen, Game * g);
  void addResource(ResourceType r, int qty);
  bool buildProperty(int id);
  bool buildRoad(int id);
  bool turn();
  std::string getPlayerFirstLetter(); // used for text display
  std::string save();

  void addProperty(int id, std::weak_ptr<Property> p);
  void addRoad(int id, std::weak_ptr<Road> r);
  void setResources(const PlayerData & pd);
  std::string getColour() const;
  int totalResources();
  void initTurn();
  std::string getDiceType();

private:
  bool buildBeginningProperty(int id);
  void subtractResource(ResourceType r, int qty);
  ResourceType getRandomResource();
  void upgradeProperty(int id);
  bool placeGoose(int id);
  int howManyResources(ResourceType r);
  void rollDice();
  void printStatus();
  void printOwnedBuildings();
  void setDiceToLoaded();
  void setDiceToFair();
  void rolledSeven();
  void printResourcesChange();
  bool anyResourcesGained();
  int totalChangeInResources();
  bool canUpgrade(int id);
  bool enoughResources(std::string p);
  bool enoughResourcesToUpgrade(int id);
  void clearChangeInResources();
  std::string steal(std::string playerColour);
  void discardHalf();
  void trade(std::string player, std::string give, std::string take);
  ResourceType convertToResourceType(std::string r);
  bool hasResources(std::string playerColour);
};

#endif
