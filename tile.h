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

class Tile : public Subject, public Observer {

  ResourceType r;
  int id;
  int diceValue;
  bool hasGoose = false;

  std::vector<std::weak_ptr<Property>> properties;
  std::vector<std::weak_ptr<Road>> roads;

public:

  Tile(ResourceType r, int id, int dv);

  ResourceType getResourceType();
  void notify(Subject& whoNotified) override;
  SubscriptionType subType() const override;
  Info getInfo() const override;

  void addProperty(std::shared_ptr<Property> p);

  void setResourceType(ResourceType rt);

  void setDiceValue(int dv);


};

#endif
