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

class Player: public std::enable_shared_from_this<Player> {
  std::string colour;
  int numPoints;
  std::map<int, std::weak_ptr<Property>> properties;
  /* std::map<int, std::shared_ptr<Road>> roads; */
  std::vector<int> resources;
  std::vector<int> changeInResources;
  std::weak_ptr<Dice> diceChosen;
  Game * g;

public:
  Player(std::string colour, std::weak_ptr<Dice> diceChosen, Game * g);
  void addResource(ResourceType r, int qty);
  void subtractResource(ResourceType r, int qty);
  void buildProperty(int id);
  void upgradeProperty(int id);
  void turn();
  void printStatus();
  void printOwnedBuildings();
  void setDiceToLoaded();
  bool hasWon();
  void setDiceToFair();
  std::string getPlayerFirstLetter(); // used for text display
  ResourceType getRandomResource();
  std::string save();

  // SETTERS/GETTERS
  void addProperty(int id, std::weak_ptr<Property> p);
  // void addRoad(int id, weak_ptr<Road> r);  TODO: uncomment when add roads
  void setResources(const PlayerData & pd);
  int totalResources();
  int howManyResources(ResourceType r);

  std::string getColour() const;

private:
  void rollDice();
  void rolledSeven();
  void printResourcesGained();
  bool anyResourcesGained();
  int totalChangeInResources();
  bool enoughResources(std::string p);
  bool enoughResourcesToUpgrade(int id);
  void clearChangeInResources();
};

#endif
