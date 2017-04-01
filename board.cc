#include "board.h"
#include "resources.h"

Board::Board() {
  tiles[0] = make_shared<Tile>(ResourceType::Brick,0);
  properties[0] = make_shared<Property>(0);
  tiles[0].attach(properties[0]);
}
