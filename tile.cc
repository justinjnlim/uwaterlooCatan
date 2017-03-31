#include "tile.h"

void Tile::notify(BoardSubject& whoNotified) {
  if (!hasGoose) {
    notifyObservers(SubscriptionType::Tile); 
  }
}

SubscriptionType Tile::subType() {
  return SubscriptionType::Board;
}

void Tile::setGoose() {
  hasGoose = true;
}

void Tile::unsetGoose() {
  hasGoose = false;
}

int Tile::getId() {
  return id;
}

ResourceType Tile::getResourceType() {
  return r;
}

