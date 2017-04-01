#include "board.h"
#include "resources.h"
using namespace std;

Board::Board() {
  tiles[0] = make_shared<Tile>(ResourceType::Brick,0);
  properties[0] = make_shared<Property>(0);
  tiles[0].attach(properties[0]);
}

shared_ptr<Property> buildProperty(int id, shared_ptr<Player> player) {
  return properties[id]->buy(player);
}

void getDiceRoll(int diceRoll) {
  for (auto i : tiles[diceRoll])
    i->notify(this);
}

