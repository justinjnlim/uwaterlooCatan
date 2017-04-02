#include "tile.h"
#include "subject.h"
#include "observer.h"
#include "subscriptions.h"
using namespace std;

using namespace std;

Tile::Tile(ResourceType r, int id, int dv): r{r}, id{id}, diceValue{dv} {}

void Tile::notify(Subject& whoNotified) {
  cout << "I'm being notified" << endl;
  Info board = whoNotified.getInfo();
  if (!hasGoose && board.value == diceValue) {
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

void Tile::addProperty(shared_ptr<Property> p) {
  properties.emplace_back(p);
}

void Tile::setResourceType(ResourceType rt) {
  r = rt;
}

void Tile::setDiceValue(int dv) {
  diceValue = dv;
}
