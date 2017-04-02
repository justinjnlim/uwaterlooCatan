#include "board.h"
#include "resources.h"
#include "tile.h"
#include "property.h"
#include "player.h"
#include "game.h"
using namespace std;

Board::Board(Game * g): g{g} {
  tiles.emplace_back(make_shared<Tile>(ResourceType::Brick, 5, 5));
  properties.emplace_back(make_shared<Property>(5));
  attach(tiles[0]);
  tiles[0]->attach(properties[0]);

  for(int i = 0; i < 18; ++i) { // TODO: hardcoded
    tiles.emplace_back(make_shared<Tile>(ResourceType::Brick, i, 0)); // default values so setUp is called after
    attach(tiles[i]);
  }

  for(int i = 0; i < 53; ++ i) { // TODO: max properties;
    properties.emplace_back(make_shared<Property>(i));
  }
  // LINK THESE MOTHERFUCKERS
  // PROPERTY LINKING
  for(int i = 0; i < 19; ++i) {
    int start = 2*i;
    if (i > 5) ++start;
    if (i > 7) ++start;
    if (i > 10) ++start;
    if (i > 12) ++start;
    if (i > 15) start += 3;
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
  return properties[0]->buy(player);
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

void Board::randomizeTiles() {
  for(int i = 0; i < 18; ++i) { // TODO: hardcoded
    tiles[i]->setResourceType(getRandomResource()); // sets all to random resource
  }
  vector<int> diceVals= {2, 12};
  for(int i = 0; i < 2; ++i) {
    diceVals.emplace_back(g->genRand(3,6));
  }

  // create array of posibble values, use shuffle, with seed from joseph
  tiles[0]->setDiceValue(2);
  tiles[12]->setDiceValue(2); // TODO: RANDOMIZE DICE VALUES
}


ResourceType Board::getRandomResource() {
  int sumWeight = 0;
  for(auto i : resourceDistribution) sumWeight += i;
  int randNum = g->genRand(1, sumWeight);
  for(int i = 0; i < NUMRESOURCES; ++i) {
    if(randNum < resourceDistribution[i]) {
      resourceDistribution[i] -= 1;
      return static_cast<ResourceType>(i);
    } else {
      randNum -= resourceDistribution[i];
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
