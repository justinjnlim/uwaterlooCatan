#ifndef _PROPERTY_H_
#define _PROPERTY_H_
#include <vector>
#include <string>
#include "observer.h"
#include "player.h"
#include "road.h"
#include "resources.h"
#include "propertytypes.h"
#include "subject.h"
#include "subscriptions.h"
#include "tile.h"

// Represents the Properties on the Ctor game board
class Property : public Subject, public Observer, public std::enable_shared_from_this<Property> {
  std::weak_ptr<Player> owner;
  int id;
  PropertyType p = PropertyType::Unowned;
  std::vector<std::weak_ptr<Road>> neighbours;

  public:

  // Constructor requires property id
  Property(int id);

  void printNeighbours();

  // Allows a player to buy the property, take ownership and upgrade
  std::shared_ptr<Property> buy(std::shared_ptr<Player> player, int multiple = 1);
  // Upgrades the property
  void upgrade();
  void addNeighbour(std::weak_ptr<Road> neighbour);
  void notify(Subject& whoNotified) override;
  
  // Getters

  // Check if Property is adjacent to a road of a given colour
  bool attachedToColourRoad(std::string);
  // Checks if conditions are good for a player to build here
  bool canBuild(std::string colour);
  // Checks to build at init stage of game
  bool canInitBuild(std::string colour);
  bool hasOwner();
  SubscriptionType subType() const override;
  std::string getBuildingType() const;
  std::string getBuildingUpgraded() const;
  PropertyType getPropertyType() const;
  Info getInfo() const override;
  std::string getOwnerColour();
  bool ownerHasResources();
};

#endif
