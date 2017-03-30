#include "tile.h"

void Tile::notify(BoardSubject& whoNotified) {
  if (!hasGoose) {
    notifyObservers(SubscriptionType::Tile); 
  }
}

SubscriptionType Tile::subType() {
  return SubscriptionType::Board;
}
