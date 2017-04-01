#ifndef _PROPERTY_H_
#define _PROPERTY_H_
#include <vector>
#include "observer.h"
#include "player.h"
#include "road.h"
#include "resources.h"
#include "propertytypes.h"
#include "subject.h"
#include "subscriptions.h"

class Property : public Observer, public std::enable_shared_from_this<Property> {
  std::shared_ptr<Player> owner = nullptr;
  int id;
  PropertyType p = PropertyType::Unowned;
//  std::vector<Road*> neighbours;

  public:

  Property(int id);
  
  std::shared_ptr<Property> buy(std::shared_ptr<Player> player);
  void upgrade();
//  bool hasOwner();
//  void addNeighbour(Road* nb);
  void notify(Subject& whoNotified);
//  bool hasNeighbouringRoad(int id);
  SubscriptionType subType();

};

#endif
