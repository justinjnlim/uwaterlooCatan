#include "property.h"

using namespace std;

Property::Property(int id): id{id} {}

shared_ptr<Property> Property::buy(shared_ptr<Player> player) {
  upgrade();
  owner = player;

  // TELL THE FUCKIN DISPLAY!!!

  return shared_from_this();
}

void Property::upgrade() {
  ++p;
  // TELL THE DISPLAY
}

void Property::notify(Subject& whoNotified) {
  owner->addResource(whoNotified.getResourceType(),static_cast<int>(p));
}

SubscriptionType Property::subType() {
  return SubscriptionType::Property;
}
