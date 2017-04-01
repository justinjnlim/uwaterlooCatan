#ifndef _TILE_H_
#define _TILE_H_
#include <vector>
#include <memory>
#include "resources.h"
#include "subscriptions.h"
#include "road.h"
#include "property.h"
#include "subject.h"
#include "observer.h"

class Tile : public Subject, public Observer {

  ResourceType r;
  int id;
  bool hasGoose = false;

public:

  Tile(ResourceType r, int id);

  ResourceType getResourceType();
  void notify(Subject& whoNotified);
  SubscriptionType subType();

}

#endif
