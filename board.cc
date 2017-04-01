#include "board.h"
#include "resources.h"
#include "tile.h"
#include "property.h"
#include "player.h"
using namespace std;

Board::Board() {
  tiles[0] = {make_shared<Tile>(ResourceType::Brick,0)};
  properties[0] = make_shared<Property>(0);
  tiles[0][0]->attach(properties[0]);
}

shared_ptr<Property> Board::buildProperty(int id, shared_ptr<Player> player) {
  return properties[id]->buy(player);
}

void Board::getDiceRoll(int diceRoll) {
  for (auto i : tiles[diceRoll])
    i->notify(*this);
}

Info Board::getInfo() const {}
