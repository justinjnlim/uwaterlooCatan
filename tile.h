#ifndef _TILE_H_
#define _TILE_H_
#include <vector>
#include "resources.h"
#include "subscriptions.h"
#include "road.h"
#include "property.h"
#include "subject.h"
#include "observer.h"

class Tile : public TileSubject, public BoardObserver {

  ResourceType r;
  int id;
  bool hasGoose;

public:
  Tile(ResourceType r, int id);

  void notify(BoardSubject& whoNotified);
  SubscriptionType subType();

}

#endif
