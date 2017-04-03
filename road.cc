#include <iostream>
#include "road.h"
#include "property.h"
using namespace std;

Road::Road(int id): id{id}, owner{weak_ptr<Player>()} {}

shared_ptr<Road> Road::buy(shared_ptr<Player> player) {
  owner = player;
  notifyObservers(SubscriptionType::Display);

  return shared_from_this();
}

void Road::addNeighbour(weak_ptr<Property> neighbour) {
  neighbours.emplace_back(neighbour);
}

void Road::printNeighbours() {
  cout << "Road " << id << " has neighbours:" << endl;
  for (weak_ptr<Property> p : neighbours) {
    cout << (p.lock())->getInfo().ownerString << endl;
  }
}

int Road::getId() {
  return id;
}

Info Road::getInfo() const {
  Info i;
  i.value = id;
  i.type = "Road";
  i.hasGoose = false;
  if (!owner.expired()) {
    i.ownerString = (owner.lock())->getPlayerFirstLetter() + "R";
  }
}

bool Road::hasAdjacentProperty() {
  for (weak_ptr<Property> p : neighbours) {
    if (!p.expired()) {
      (p.lock())->hasOwner == true) return true;
    }
  }
  return false;
}

bool Road::hasOwner() {
  return !(owner.expired);
}

string Road::getOwnerColour() {
  if (owner.expired()) {
    return "";
  } else {
    return (owner.lock())->getColour();
  }
}

bool Road::canBuild(string colour) {
  if (owner.expired()) {
    for (weak_ptr<Property> p : neighbours) {
      if (!p.expired()) {
        if ((p.lock())->getOwnerColour == colour || (p.lock())->attachedToColourRoad(colour)) return true;
      }
    }
  }
  return false;
}
