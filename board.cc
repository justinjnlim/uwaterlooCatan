#include "board.h"
#include "resources.h"
#include "tile.h"
#include "property.h"
#include "road.h"
#include "player.h"
using namespace std;

Board::Board() {
  // tiles.emplace_back(make_shared<Tile>(ResourceType::Brick, 5, 5));
  // properties.emplace_back(make_shared<Property>(5));
  // attach(tiles[0]);
  // tiles[0]->attach(properties[0]);

  for(int i = 0; i < 19; ++i) { // TODO: hardcoded
    tiles.emplace_back(make_shared<Tile>(ResourceType::Brick, i, 5)); // default values so setUp is called after
    attach(tiles[i]);
  }

  for (int i = 0; i < 72; ++i) { // TODO: max roads
    roads.emplace_back(make_shared<Road>(i));
  }

  for (int i = 0; i < 54; ++i) { // TODO: max properties;
    properties.emplace_back(make_shared<Property>(i));
  }

  linkRoadsAndProperties();

  for (weak_ptr<Road> r : roads) {
    (r.lock())->printNeighbours();
  }

  // LINK THESE MOTHERFUCKERS
  // PROPERTY LINKING
  for (int i = 0; i < 19; ++i) {
    int start = 2*i;
    if (i > 5) ++start;
    if (i > 7) ++start;
    if (i > 10) ++start;
    if (i > 12) ++start;
    if (i > 15) ++start;
    if (i > 17) start += 3;
    // TODO WRITE THIS ADDPROPERTY FUNCTION
    tiles[i]->addProperty(properties[start]);
    tiles[i]->addProperty(properties[start+1]);
    if (i == 0) {
      tiles[i]->addProperty(properties[start+3]);
      tiles[i]->addProperty(properties[start+4]);
      tiles[i]->addProperty(properties[start+8]);
      tiles[i]->addProperty(properties[start+9]);
    } else if (i < 3) {
      tiles[i]->addProperty(properties[start+5]);
      tiles[i]->addProperty(properties[start+6]);
      tiles[i]->addProperty(properties[start+11]);
      tiles[i]->addProperty(properties[start+12]);
    } else if (i < 16) {
      tiles[i]->addProperty(properties[start+6]);
      tiles[i]->addProperty(properties[start+7]);
      tiles[i]->addProperty(properties[start+12]);
      tiles[i]->addProperty(properties[start+13]);
    } else if (i < 18) {
      tiles[i]->addProperty(properties[start+6]);
      tiles[i]->addProperty(properties[start+7]);
      tiles[i]->addProperty(properties[start+11]);
      tiles[i]->addProperty(properties[start+12]);
    } else {
      tiles[i]->addProperty(properties[start+5]);
      tiles[i]->addProperty(properties[start+6]);
      tiles[i]->addProperty(properties[start+8]);
      tiles[i]->addProperty(properties[start+9]);
    }
  }
}

shared_ptr<Property> Board::buildProperty(int id, shared_ptr<Player> player) {
  return properties[id]->buy(player);
}

void Board::setupTiles(string layout) {
  int resource;
  int dicevalue;

  for(int i = 0; i < 18; ++i) { // TODO: hardcoded
    istringstream(layout) >> resource;
    istringstream(layout) >> dicevalue;

    tiles[i]->setResourceType(static_cast<ResourceType>(resource));
    tiles[i]->setDiceValue(dicevalue);

  }
}

void Board::linkRoadsAndProperties() {
  // horizontal roads in main square
  int id = 9;
  int proxyID; // for vertical road linking pattern
  int horizontalSubtractor = 3;
  int verticalSubtractor = 0;
  int top, bottom, left, right; // cardinal neighbours
  while (id < 63) {
    // initiates horizontal road linking pattern

    left = id - horizontalSubtractor;
    roads[id]->addNeighbour(properties[left]);
    properties[left]->addNeighbour(roads[id]);

    right = left + 1;
    roads[id]->addNeighbour(properties[right]);
    properties[right]->addNeighbour(roads[id]);

    // id reaches end of horizontal road row
    if (id == 11 || id == 19 || id == 28 || id == 36 || id == 45 || id == 53) {
      // initiates vertical road linking pattern
      int constSubtractor = verticalSubtractor;

      if (id == 11 || id == 28 || id == 45 || id == 53)
        verticalSubtractor += 2;
      else
        verticalSubtractor += 3;

      for (int i = 0; i < 6; i++) {
        id++;
        proxyID = id - constSubtractor;
        top = proxyID - (proxyID % 6) - (6 - i);
        bottom = proxyID - (proxyID % 6) + i;
        roads[id]->addNeighbour(properties[top]);
        properties[top]->addNeighbour(roads[id]);
        roads[id]->addNeighbour(properties[bottom]);
        properties[bottom]->addNeighbour(roads[id]);
      }

      horizontalSubtractor += 5;
    }

    id++;
    horizontalSubtractor--;
  }
}

// void Board::randomizeTiles() {
//   vector<int> resSpec = [4,4,4,3,3,1];
//   for(int i = 0; i < 18; ++i) { // TODO: hardcoded
//     tiles[i]->setResourceType(static_cast<ResourceType>(resource));
//     tiles[i]->setDiceValue(dicevalue);
//
//   }
// }

void Board::getDiceRoll(int diceRoll) {
  diceValue = diceRoll;
  notifyObservers(SubscriptionType::Tile);
}

Info Board::getInfo() const {
  Info ret = {diceValue};
  return ret;
}
