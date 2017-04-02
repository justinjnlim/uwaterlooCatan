#include "board.h"
#include "resources.h"
#include "tile.h"
#include "property.h"
#include "player.h"
using namespace std;

Board::Board() {
  tiles.emplace_back(make_shared<Tile>(ResourceType::Brick, 5, 2));
  properties.emplace_back(make_shared<Property>(5));
  attach(tiles[0]);
  tiles[0]->attach(properties[0]);
}

shared_ptr<Property> Board::buildProperty(int id, shared_ptr<Player> player) {
  return properties[0]->buy(player);
}

void Board::getDiceRoll(int diceRoll) {
  diceValue = diceRoll;
  notifyObservers(SubscriptionType::Tile);
}

Info Board::getInfo() const {
  Info ret = {diceValue};
  return ret;
}
