#include "board.h"
#include "resources.h"
#include "tile.h"
#include "property.h"
#include "player.h"
using namespace std;

Board::Board() {
  tiles[5] = {make_shared<Tile>(ResourceType::Brick, 5)};
  properties[5] = make_shared<Property>(5);
  tiles[5][0]->attach(properties[5]);
}

shared_ptr<Property> Board::buildProperty(int id, shared_ptr<Player> player) {
  return properties[id]->buy(player);
}

void Board::getDiceRoll(int diceRoll) {
  for (auto i : tiles[diceRoll])
    i->notify(*this);
}

Info Board::getInfo() const {}
