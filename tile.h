#ifndef _TILE_H_
#define _TILE_H_
#include <vector>
#include "resources.h"
#include "subscriptions.h"
#include "road.h"
#include "property.h"
#include "subject.h"
#include "observer.h"

class Tile : public Subject, public Observer {

  ResourceType r;
  int id;
  bool hasGoose;
  std::vector<Road*> roads;
  std::vector<Property*> properties;

public:
  bool canYield(int requestedDV);
  void notify(Subject& whoNotified);
  SubscriptionType subType();

}

#endif
