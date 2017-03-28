#ifndef _BOARD_H_
#define _BOARD_H_
#include <map>
#include "property.h"
#include "road.h"
#include "subject.h"
#include "tile.h"

class Board : public Subject {

  std::map<int,Road*> roads;
  std::map<int,Property*> properties;
  std::map<int,Tile*> tiles;

public:
  void save();

}

#endif
