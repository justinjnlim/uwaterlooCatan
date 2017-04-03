#include "tile.h"
#include "subject.h"
#include "observer.h"
#include "subscriptions.h"
#include <iostream>

using namespace std;

Tile::Tile(ResourceType r, int id, int dv): r{r}, id{id}, diceValue{dv} {}

void Tile::notify(Subject& whoNotified) {
  cout << "Tile " << id << " was notified. DiceValue: " << diceValue << endl;

  for (weak_ptr<Road> r : roads) {
    cout << "Has Road " << (r.lock())->getId() << endl;
  }

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
  i.value = id;
  i.type = "Tile";
  i.hasGoose = hasGoose;
  i.rt = r;
  i.ownerString = to_string(diceValue);

  return i;
}

int Tile::getDiceValue() {
  return diceValue;
}

void Tile::addProperty(shared_ptr<Property> p) {
  properties.emplace_back(p);
  attach(p);
}

void Tile::addRoad(shared_ptr<Road> r) {
  roads.emplace_back(r);
}

void Tile::setResourceType(ResourceType rt) {
  r = rt;
}

void Tile::setDiceValue(int dv) {
  diceValue = dv;
}

bool Tile::getHasGoose() {
  return hasGoose;
}

int Tile::getAddress() {
  return id;
}

void Tile::removeGoose() {
  cout << "this method was called" << endl;
  hasGoose = false;
  // notify TD
}

bool Tile::addGoose() {
  cout << "this method was also called" << endl;
  hasGoose = true;
  // notify TD
}
