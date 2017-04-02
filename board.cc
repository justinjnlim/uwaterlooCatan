#include "textdisplay.h"
#include "resources.h"
#include "tile.h"
#include "property.h"
#include "road.h"
#include "player.h"
#include "game.h"
#include "board.h"
using namespace std;

Board::Board(Game * g): td{make_shared<TextDisplay>()}, g{g} {
  // tiles.emplace_back(make_shared<Tile>(ResourceType::Brick, 5, 5));
  // properties.emplace_back(make_shared<Property>(5));
  // attach(tiles[0]);
  // tiles[0]->attach(properties[0]);

  for(int i = 0; i < NUMTILES; ++i) { // TODO: hardcoded
    tiles.emplace_back(make_shared<Tile>(ResourceType::Brick, i, 5)); // default values so setUp is called after
    attach(tiles[i]);
    tiles[i]->attach(td);
  }

  for (int i = 0; i < NUMROADS; ++i) { // TODO: max roads
    roads.emplace_back(make_shared<Road>(i));
    roads[i]->attach(td);
  }

  for (int i = 0; i < NUMPROPERTIES; ++i) { // TODO: max properties;
    properties.emplace_back(make_shared<Property>(i));
    properties[i]->attach(td);
  }

  linkAssets();

  // // check roads' neighbours
  // for (weak_ptr<Road> r : roads) {
  //   (r.lock())->printNeighbours();
  // }

  // // check properties' neighbours
  // for (weak_ptr<Property> p : properties) {
  //   (p.lock())->printNeighbours();
  // }
}

void Board::printTiles() {
  for (weak_ptr<Tile> t : tiles) {
    cout << "Resource Type: " << static_cast<int>((t.lock())->getInfo().rt) << endl;
    cout << "Dice Value: " << (t.lock())->getDiceValue() << endl;
  }
}

shared_ptr<Property> Board::buildProperty(int id, shared_ptr<Player> player) {
  return properties[id]->buy(player);
}

void Board::setupTiles(string layout) {
  cout << layout << endl;

  int resource;
  int dicevalue;
  istringstream ss{layout};
  for(int i = 0; i < NUMTILES; ++i) {
    ss >> resource;
    ss >> dicevalue;
    tiles[i]->setResourceType(static_cast<ResourceType>(resource));
    tiles[i]->setDiceValue(dicevalue);
  }
}

void Board::linkAssets() {
  linkTiles_Roads(); // TODO Implement this
  linkTiles_Properties();
  linkRoads_Properties();
}

void Board::linkTiles_Roads() {
  int start=0, extra=2, jump=0, bot=7, vert=8;
  for (int i = 0; i < NUMTILES; ++i) {
    extra -= 2;
    ++jump;
    --bot;
    if (i == 1) extra = 0;
    if (i == 3) {
      extra += 4;
      jump = 3;
    }
    if (i == 6 || i == 8 || i == 11 || i == 13 || i == 16 || i == 18) {
      extra += 6;
      jump = 3;
    }
    if (i == 3 || i == 8 || i == 13) bot = 6;
    if (i == 1 || i == 6 || i == 11) bot = 5;
    if (i == 16) bot = 4;

    if (i == 6 || i == 11) vert = 9;
    if (i == 8 || i == 13) vert = 8;

    start = 3*i + extra;

    if (i == 18) start = 61;

    tiles[i]->addRoad(roads[start]);
    if (i == 0) {
      tiles[i]->addRoad(roads[start+1]);
      tiles[i]->addRoad(roads[start+2]);
      tiles[i]->addRoad(roads[start+6]);
      tiles[i]->addRoad(roads[start+7]);
      tiles[i]->addRoad(roads[start+10]);
    } else if (i < 18) {
      tiles[i]->addRoad(roads[start+jump]);
      tiles[i]->addRoad(roads[start+jump+1]);
      tiles[i]->addRoad(roads[start+jump+vert]);
      tiles[i]->addRoad(roads[start+jump+vert+1]);
      tiles[i]->addRoad(roads[start+jump+vert+bot]);
    } else if (i == 18) {
      tiles[i]->addRoad(roads[start+jump]);
      tiles[i]->addRoad(roads[start+jump+1]);
      tiles[i]->addRoad(roads[start+jump+5]);
      tiles[i]->addRoad(roads[start+jump+6]);
      tiles[i]->addRoad(roads[start+jump+7]);
    }
  }
}

void Board::linkTiles_Properties() {
  for (int i = 0; i < NUMTILES; ++i) {
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

void Board::linkRoads_Properties() {
  int id = 0;

  // main square stuff
  int proxyID; // for vertical road linking pattern
  int horizontalSubtractor;
  int verticalSubtractor;
  int topSubtractor; // used in non-main square tiles
  int bottomSubtractor; // used in non-main square tiles
  int constSubtractor;
  int top, bottom, left, right; // cardinal neighbours  while (id < 72) {}

  while (id < 72) {
    if (id < 9) {
      horizontalSubtractor = 0;

      while (id < 9) {
        left = id - horizontalSubtractor;
        roads[id]->addNeighbour(properties[left]);
        properties[left]->addNeighbour(roads[id]);

        right = left + 1;
        roads[id]->addNeighbour(properties[right]);
        properties[right]->addNeighbour(roads[id]);

        if (id == 0 || id == 4) {
          if (id == 0) {
            topSubtractor = 1;
            bottomSubtractor = -2;

            for (int i = 0; i < 2; i++) {
              id++;
              top = id - topSubtractor;
              bottom = id - bottomSubtractor;
              roads[id]->addNeighbour(properties[top]);
              properties[top]->addNeighbour(roads[id]);
              roads[id]->addNeighbour(properties[bottom]);
              properties[bottom]->addNeighbour(roads[id]);
            }
          } else if (id == 4) {
            topSubtractor = 3;
            bottomSubtractor = -2;

            for (int i = 0; i < 4; i++) {
              id++;
              top = id - topSubtractor;
              bottom = id - bottomSubtractor;
              roads[id]->addNeighbour(properties[top]);
              properties[top]->addNeighbour(roads[id]);
              roads[id]->addNeighbour(properties[bottom]);
              properties[bottom]->addNeighbour(roads[id]);
            }
          }
          horizontalSubtractor += 2;
        }

        horizontalSubtractor--;
        id++;
      }
    } else if (id > 8 && id < 63) {
      horizontalSubtractor = 3;
      verticalSubtractor = 0;

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
          constSubtractor = verticalSubtractor;

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

        horizontalSubtractor--;
        id++;
      }
    } else {
      topSubtractor = 20;
      bottomSubtractor = 15;

      while (id < 72) {
        top = id - topSubtractor;
        bottom = id - bottomSubtractor;
        roads[id]->addNeighbour(properties[top]);
        properties[top]->addNeighbour(roads[id]);
        roads[id]->addNeighbour(properties[bottom]);
        properties[bottom]->addNeighbour(roads[id]);

        if (id == 66 || id == 70) {
          if (id == 66) {
            horizontalSubtractor = 19;

            for (int i = 0; i < 2; i++) {
              id++;
              left = id - horizontalSubtractor;
              right = left + 1;
              roads[id]->addNeighbour(properties[left]);
              properties[left]->addNeighbour(roads[id]);
              roads[id]->addNeighbour(properties[right]);
              properties[right]->addNeighbour(roads[id]);

              horizontalSubtractor--;
            }

            bottomSubtractor += 2;
          } else if (id == 70) {
            horizontalSubtractor = 19;

            id++;
            left = id - horizontalSubtractor;
            right = left + 1;
            roads[id]->addNeighbour(properties[left]);
            properties[left]->addNeighbour(roads[id]);
            roads[id]->addNeighbour(properties[right]);
            properties[right]->addNeighbour(roads[id]);
          }
        }
        id++;
      }
    }
  }
}

// tiles.emplace_back(make_shared<Tile>(ResourceType::Brick, 5, 5));
// properties.emplace_back(make_shared<Property>(5));
// attach(tiles[0]);
// tiles[0]->attach(properties[0]);

void Board::randomizeTiles() {
  shuffle(resourceDistribution.begin(), resourceDistribution.end(), g->getRandEng());
  shuffle(diceDistribution.begin(), diceDistribution.end(), g->getRandEng());

  int j = 0;
  for(int i = 0; i < NUMTILES; ++i) {
    tiles[i]->setResourceType(static_cast<ResourceType>(resourceDistribution[i]));
    if(tiles[i]->getResourceType() == ResourceType::Park) {
      tiles[i]->setDiceValue(0);
    } else {
      tiles[i]->setDiceValue(diceDistribution[j]);
      ++j;
    }
  }
}

void Board::getDiceRoll(int diceRoll) {
  diceValue = diceRoll;
  notifyObservers(SubscriptionType::Tile);
}

Info Board::getInfo() const {
  Info ret = {diceValue};
  return ret;
}

bool Board::addGoose(int id) {
  for(auto tile : tiles) {
    if(tile->getHasGoose() && tile->getAddress() == id) { // placing on same address
      return false;
    } else if(tile->getHasGoose()){ // remove goose current
      tile->removeGoose();
    } else if(tile->getAddress() == id) { // add goose
      tile->addGoose();
    }
  }
  return true;
}

ostream &operator<<(ostream &out, shared_ptr<Board> b) {
  out << *(b.td);
  return out;
}
