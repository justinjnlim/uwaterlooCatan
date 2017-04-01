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

class Property : public Observer {
  Player* owner = nullptr;
  int id;
  PropertyType p = 0;
  std::vector<Road*> neighbours;

  void payOwner(ResourceType r);

  public:

  Property(int id);
  bool hasOwner();
  void addNeighbour(Road* nb);
  void notify(Subject& whoNotified);
  bool hasNeighbouringRoad(int id);
  SubscriptionType subType();

};

#endif
