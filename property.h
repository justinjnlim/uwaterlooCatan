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
/* class Player; */
class Property : public Subject, public Observer, public std::enable_shared_from_this<Property> {
  std::weak_ptr<Player> owner;
  int id;
  PropertyType p = PropertyType::Unowned;
  std::vector<std::weak_ptr<Road>> neighbours;

  public:

  Property(int id);

  void printNeighbours();

  std::shared_ptr<Property> buy(std::shared_ptr<Player> player, int multiple = 1);
  void upgrade();
  bool hasOwner();
  void addNeighbour(std::weak_ptr<Road> neighbour);
  void notify(Subject& whoNotified) override;
  std::string getOwnerColour() const;
  bool attachedToColourRoad(std::string);
  bool canBuild(std::string colour);
  bool canInitBuild(std::string colour);

  SubscriptionType subType() const override;
// used to get the letter of it's property type for Player::printStatus
  std::string getBuildingType() const;
  std::string getBuildingUpgraded() const;
  // get the enum for property type
  PropertyType getPropertyType() const;
  Info getInfo() const override;
  std::string getOwnerColour();
  bool ownerHasResources();
};

#endif
