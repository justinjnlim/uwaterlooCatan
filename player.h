#ifndef _PLAYER_H_
#define _PLAYER_H
#include <string>
#include <vector>
#include <iostream>

class Player {
  std::string colour;
  int numPoints;
  std::vector<Property **> properties;
  std::vector<Road *> roads;
  std::vector<ResourceType> resources;
  Dice * diceChosen;
  Game * g;

public:
  void turn(std::istream &in); // not sure about istream part
  void initTurn(std::istream &in);

private:
  // resource accessors/mutators
  void howManyResources(ResourceType r);
  void addResource(ResourceType r, int qty);
  void subtractResource(ResourceType r, int qty);

  // for discard half and steal random
  ResourceType getRandomResource();

  // can do these actions on turn
  void setDice(); // can choose fair or loaded
  void rollDice();

  void buildRoad(int id);
  void buildProperty(int id);
  void upgradeProperty(int id);
  void placeGoose(int id);
  void trade(Player *p, ResourceType r);

  void passTurn();
  std::string printStatuses(); // prints all builder statuses
  std::string printBoard();
  std::string printOwnedProperties();
  void save();

  // if roll 7 and place goose on tile, choose to steal from player p
  void steal(Player *p);

};

#endif
