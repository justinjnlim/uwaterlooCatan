#ifndef _TILE_H_
#define _TILE_H_
#include <vector>
#include <memory>
#include <iostream>
#include "resources.h"
#include "subscriptions.h"
#include "road.h"
#include "property.h"
#include "subject.h"
#include "observer.h"

// Represents the Tiles on the Ctor game board
class Tile : public Subject, public Observer {

  ResourceType r;
  int id;
  int diceValue;
  bool hasGoose = false;

  std::vector<std::weak_ptr<Property>> properties;
  std::vector<std::weak_ptr<Road>> roads;

public:

  // Constructs with the resource, id, and dice value
  Tile(ResourceType r, int id, int dv);
  
  // Notify tells all observing properties to pay their owners
  void notify(Subject& whoNotified) override;

  // Setters
  void addProperty(std::shared_ptr<Property> p);
  void addRoad(std::shared_ptr<Road>r);
  void setResourceType(ResourceType rt);
  void setDiceValue(int dv);
  void removeGoose();
  bool addGoose();
  
  // Getters
  int getAddress();
  int getDiceValue();
  bool getHasGoose();
  std::string whoLivesHere(std::string self);
  ResourceType getResourceType();
  SubscriptionType subType() const override;
  Info getInfo() const override;

};

#endif
