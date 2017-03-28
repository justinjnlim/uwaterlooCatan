#ifndef _ROAD_H_
#define _ROAD_H_
#include <vector>
#include "player.h"
#include "property.h"

class Road {
  Player* owner;
  int id;
  std::vector<Property*> neighbours;
  public:
  bool hasAdjacentProperty();
  bool hasOwner();
  bool hasNeighbourRoad(int id);
};

#endif
