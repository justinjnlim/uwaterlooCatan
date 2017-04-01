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
