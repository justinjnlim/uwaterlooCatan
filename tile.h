#ifndef _TILE_H_
#define _TILE_H_
#include <vector>
#include "resources.h"
#include "subscriptions.h"
#include "road.h"
#include "property.h"
#include "tileSubject.h"
#include "boardObserver.h"

class Tile : public TileSubject, public BoardObserver {

  ResourceType r;
  int id;
  bool hasGoose;

public:
  Tile(ResourceType r, int id);

  void notify(BoardSubject& whoNotified);
  SubscriptionType subType();

  void setGoose();
  void unsetGoose();
  
  int getId();
  ResourceType getResourceType();

}

#endif
