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
  cout << "I'm adding resource now" << endl;
  owner->addResource(whoNotified.getInfo().rt, static_cast<int>(p));
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
  i.type = "Property";
  i.hasGoose = false;
  i.rt;
  if(p == PropertyType::Unowned) {
    if(id < 10) {
      i.ownerString = " " + to_string(id);
    } else {
      i.ownerString = to_string(id);
    }
  } else {
    i.ownerString = owner->getPlayerFirstLetter() + getBuildingType();
  }
  return i;
}
