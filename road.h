#ifndef _ROAD_H_
#define _ROAD_H_
#include <vector>
#include <memory>
#include <string>
#include "player.h"
#include "subject.h"
#include "info.h"
class Property;

// Represents the Roads on the Ctor game board
class Road : public Subject, public std::enable_shared_from_this<Road> {
  int id;
  std::weak_ptr<Player> owner;
  std::vector<std::weak_ptr<Property>> neighbours;



 public:
  // Road is constructed with an id
  Road(int id);

  // Lets a player "buy" the road, takes ownership 
  std::shared_ptr<Road> buy(std::shared_ptr<Player> player);

  // For linking to adjacent properties
  void addNeighbour(std::weak_ptr<Property> neighbour);
  void printNeighbours();

  // Getters
  int getId();
  Info getInfo() const override;
  bool hasAdjacentProperty();
  bool hasOwner();
  std::string getOwnerColour();

  // Checks if this road can be built by the player
  bool canBuild(std::string colour); 
};

#endif
