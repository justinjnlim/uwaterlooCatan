#include "tile.h"

void Tile::notify(Subject& whoNotified) {
  if (!hasGoose) {
    notifyObservers(SubscriptionType::Tile); 
  }
}

SubscriptionType Tile::subType() {
  return SubscriptionType::Board;
}
