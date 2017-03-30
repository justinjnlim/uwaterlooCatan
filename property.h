#ifndef _PROPERTY_H_
#define _PROPERTY_H_
#include <vector>
#include "tileObserver.h"
#include "player.h"
#include "road.h"
#include "resources.h"
#include "tileSubject.h"
#include "subscriptions.h"

class Property : public TileObserver {
  Player* owner;
  int id;
  std::vector<Road*> neighbours;

  virtual void payOwner(ResourceType r)=0;
  virtual char getType()=0;

  public:
  bool hasOwner();
  void addNeighbour(Road* nb);
  void notify(Subject& whoNotified);
  bool hasNeighbouringRoad(int id);
  SubscriptionType subType();

};

#endif
