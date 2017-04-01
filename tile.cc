#include "tile.h"
#include "subject.h"
#include "observer.h"
#include "subscriptions.h"

Tile::Tile(ResourceType r, int id): r{r}, id{id} {}

void Tile::notify(Subject& whoNotified) {
  if (!hasGoose) {
    notifyObservers(SubscriptionType::Property);
  }
}

ResourceType Tile::getResourceType() {
  return r;
}

SubscriptionType Tile::subType() const {
  return SubscriptionType::Tile;
}

Info Tile::getInfo() const {
  Info i;
  i.type = "Tile";
  i.hasGoose = hasGoose;
  i.rt = r;
  i.ownerString = "";

  return i;
}
