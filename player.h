#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
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
  void subtractResource(ResourceType r, int qty);
  bool buildProperty(int id);
  bool buildRoad(int id);
  void upgradeProperty(int id);
  bool turn();
  void printStatus();
  void printOwnedBuildings();
  void setDiceToLoaded();
  void setDiceToFair();
  std::string getPlayerFirstLetter(); // used for text display
  ResourceType getRandomResource();
  std::string save();
  void addRoad(int id, std::weak_ptr<Road> r);

  // SETTERS/GETTERS
  void addProperty(int id, std::weak_ptr<Property> p);
  // void addRoad(int id, weak_ptr<Road> r);  TODO: uncomment when add roads
  void setResources(const PlayerData & pd);
  int howManyResources(ResourceType r);
  bool buildBeginningProperty(int id);
  std::string getColour() const;
  bool placeGoose(int id);
  int totalResources();
  void initTurn();

private:
  void rollDice();
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
};

#endif
