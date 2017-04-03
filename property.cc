#include "property.h"
#include "tile.h"
#include <iostream>
using namespace std;

Property::Property(int id): owner{weak_ptr<Player>()}, id{id}  {}

void Property::printNeighbours() {
  cout << "Property " << id << " has neighbours:" << endl;
  for (weak_ptr<Road> r : neighbours) {
    cout << (r.lock())->getId() << endl;
  }
}

void Property::addNeighbour(weak_ptr<Road> neighbour) {
  neighbours.emplace_back(neighbour);
}

shared_ptr<Property> Property::buy(shared_ptr<Player> player, int multiple) {
  for (int i = 0; i < multiple; i++)
    upgrade();
  owner = player;

  notifyObservers(SubscriptionType::Display);

  return shared_from_this();
}

void Property::upgrade() {
  p = static_cast<PropertyType>(static_cast<int>(p) + 1);
  notifyObservers(SubscriptionType::Display);
}

void Property::notify(Subject& whoNotified) {
  if (!owner.expired())
    (owner.lock())->addResource(whoNotified.getInfo().rt, static_cast<int>(p));
}

SubscriptionType Property::subType() const {
  return SubscriptionType::Property;
}

string Property::getBuildingType() const { // used by player's printStatus function
  if (p == PropertyType::Basement) {
    return "B";
  } else if (p == PropertyType::House) {
    return "H";
  } else {
    return "T";
  }
}

PropertyType Property::getPropertyType() const {
  return p;
}

Info Property::getInfo() const {
  Info i;
  i.value = id;
  i.type = "Property";
  i.hasGoose = false;
  if (owner.expired()) {
    if(id < 10) {
      i.ownerString = " " + to_string(id);
    } else {
      i.ownerString = to_string(id);
    }
  } else {
    i.ownerString = (owner.lock())->getPlayerFirstLetter() + getBuildingType();
  }
  return i;
}

string Property::getOwnerColour() {
  if(owner.expired()) {
    return "";
  }
  return (owner.lock())->getColour();
}

bool Property::ownerHasResources() {
  if(!owner.expired()) {
    if(owner.lock()->totalResources()) return true;
  }
  return false;
}

bool Property::hasOwner() {
  return !(owner.expired());
}

bool Property::attachedToColourRoad(std::string colour) {
  for (weak_ptr<Road> r : neighbours) {
    if ((r.lock())->getOwnerColour() == colour) return true;
  }
  return false;
}

bool Property::canBuild(std::string colour) {
  if (owner.expired()) {
    // check if adjacent houses not owned
    for (weak_ptr<Road> r : neighbours) {
      if ((r.lock())->hasAdjacentProperty()) return false;
    }
    for (weak_ptr<Road> r : neighbours) {
      if ((r.lock())->getOwnerColour() == colour) return true;
    }
  }
  return false;
}

bool Property::canInitBuild(std::string colour) {
  if (owner.expired()) {
    // check if adjacent houses not owned
    for (weak_ptr<Road> r : neighbours) {
      if ((r.lock())->hasAdjacentProperty()) return false;
    }
    return true;
  }
  return false;
}

string Property::getBuildingUpgraded() const {
  if (p == PropertyType::Basement) {
    return "House";
  } else {
    return "Tower";
  }
}
