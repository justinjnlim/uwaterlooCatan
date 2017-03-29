#ifndef _PROPERTY_H_
#define _PROPERTY_H_
#include <vector>
#include "observer.h"
#include "player.h"
#include "road.h"
#include "resources.h"
#include "subject.h"
#include "subscriptions.h"

class Property : public Observer {
  Player* owner;
  int id;
  std::vector<Road*> neighbours;

  virtual void payOwner(ResourceType r)=0;

  public:
  bool hasOwner();
  void addNeighbour(Road* nb);
  void notify(Subject& whoNotified);
  bool hasNeighbouringRoad(int id);
  SubscriptionType subType();

};

#endif
