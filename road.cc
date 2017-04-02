#include <iostream>
#include "road.h"
#include "property.h"
using namespace std;

Road::Road(int id): id{id}, owner{weak_ptr<Player>()} {}

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
  i.rt;
  if (owner != nullptr) {
    i.ownerSring = (owner.lock())->getPlayerFirstLetter() + "R";
  }
}
