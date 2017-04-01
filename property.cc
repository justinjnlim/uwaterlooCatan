#include "property.h"
#include "tile.h"

using namespace std;

Property::Property(int id): id{id} {}

shared_ptr<Property> Property::buy(shared_ptr<Player> player) {
  upgrade();
  owner = player;

  // TELL THE FUCKIN DISPLAY!!!

  return shared_from_this();
}

void Property::upgrade() {
  p = static_cast<PropertyType>(static_cast<int>(p) + 1);
  // TELL THE DISPLAY
}

void Property::notify(Subject& whoNotified) {
  owner->addResource(whoNotified.getInfo().rt, static_cast<int>(p));
}

SubscriptionType Property::subType() const {
  return SubscriptionType::Property;
}
