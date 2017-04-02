#ifndef _ROAD_H_
#define _ROAD_H_
#include <vector>
#include <memory>
#include "player.h"
#include "subject.h"
#include "info.h"
class Property;

class Road : public Subject, public std::enable_shared_from_this<Road> {
  int id;
  std::weak_ptr<Player> owner;
  std::vector<std::weak_ptr<Property>> neighbours;

 public:
  Road(int id);
  void addNeighbour(std::weak_ptr<Property> neighbour);
  void printNeighbours();
  int getId();
  Info getInfo() const override;
  /* bool hasAdjacentProperty(); */
  /* bool hasOwner(); */
  /* bool hasNeighbourRoad(int id); */
};

#endif
