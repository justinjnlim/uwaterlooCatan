#ifndef _BOARD_H_
#define _BOARD_H_
#include <map>
#include <memory>
#include "property.h"
#include "road.h"
#include "subject.h"
#include "tile.h"

class Board : public Subject {

  std::map<int,std::shared_ptr<Road>> roads;
  std::map<int,std::shared_ptr<Property>> properties;
  std::map<int,std::shared_ptr<Tile>> tiles;

public:
  void save();

}

#endif
