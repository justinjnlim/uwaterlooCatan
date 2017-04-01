#ifndef _BOARD_H_
#define _BOARD_H_
#include <map>
#include <memory>
#include "property.h"
/* #include "road.h" */
#include "subject.h"
#include "tile.h"
#include "player.h"
#include "property.h"

class Board : public Subject {

  std::map<int,std::shared_ptr<Road>> roads;
  std::map<int,std::shared_ptr<Property>> properties;
  std::map<int,std::vector<std::shared_ptr<Tile>>> tiles;

public:

  Board();

  std::shared_ptr<Property> buildProperty(int id, std::shared_ptr<Player> player);

  void getDiceRoll(int diceRoll);

  void save();

};

#endif
