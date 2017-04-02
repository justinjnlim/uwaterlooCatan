#include "player.h"
#include "property.h"
#include "game.h"

using namespace std;

Player::Player(string colour, weak_ptr<Dice> diceChosen, Game * g):
colour{colour}, resources(6, 0), changeInResources(6, 0),
diceChosen{diceChosen}, g{g} {}

void Player::buildProperty(int id) {
  // converts shared ptr returned to weak_ptr
  weak_ptr<Property> w = g->getGameBoard()->buildProperty(id, shared_from_this());
  properties[id] = w;
  ++numPoints;
  cout << "buildProperty ran" << endl;
}

void Player::addResource(ResourceType r, int qty) {
  resources[static_cast<int>(r)] += qty;
  changeInResources[static_cast<int>(r)] += qty;
  cout << "addedResource ran" << endl;
}



void Player::printStatus() {
  cout << colour << " has " << numPoints << " building points, ";
  cout << resources[0] << " brick, " << resources[1] << " energy, ";
  cout << resources[2] << " glass, " << resources[3] << " heat, and ";
  cout << resources[4] <<" WiFi." << endl;
 }


 void Player::printOwnedBuildings() {
   for(auto const &address : properties) {
     cout << to_string(address.first) << " ";
     cout << address.second.lock()->getBuildingType() << endl;
   }
}


void Player::upgradeProperty(int id) {
   properties[id].lock()->upgrade();
   ++numPoints;
   cout << "upgradeProperty ran" << endl;
 }

void Player::rollDice() {
  int diceRoll = diceChosen.lock()->getDiceRoll();
  cout << "You rolled a " << diceRoll << "." << endl;
  if(diceRoll == 7) {
    rolledSeven();
  } else {
    g->getGameBoard()->getDiceRoll(diceRoll);
    int numGained = NUMPLAYERS;

    for(int i = 0; i < NUMPLAYERS; ++i) {
      if(!g->getPlayer(i)->anyResourcesGained()) {
        --numGained;
      } else {
        g->getPlayer(i)->printResourcesGained();
      }
    }
    if(!numGained) { // no one gained resources
      cout << "No builders gained resources." << endl;
    }
  }

}

bool Player::anyResourcesGained() {
  return totalChangeInResources() > 0;
}

void Player::printResourcesGained() {
  cout << "Builder " << colour << " gained:" << endl;
  if(resources[0]) cout << resources[0] << " " << "BRICK" << endl;
  if(resources[1]) cout << resources[1] << " " << "ENERGY" << endl;
  if(resources[2]) cout << resources[2] << " " << "GLASS" << endl;
  if(resources[3]) cout << resources[3] << " " << "HEAT" << endl;
  if(resources[4]) cout << resources[4] << " " << "WIFI" << endl;
  clearChangeInResources();
}

void Player::rolledSeven() {

}

void Player::turn() {
  string cmd;
  while(cin >> cmd) {
    if(cmd == "load") {
      setDiceToLoaded();
    } else if(cmd == "fair") {
      setDiceToFair();
    } else if (cmd == "roll") {
      rollDice();
      break; // exits loop once rolled
    } else {
      cout << "Invalid Command." << endl;
    }
   }
  int address;

  while(cin >> cmd) {
    if(cmd == "board") {

    } else if(cmd == "status") {
      for(int i = 0; i < NUMPLAYERS; ++i) {
        g->getPlayer(i)->printStatus();
      }
    } else if(cmd == "residences") {
       printOwnedBuildings();
    } else if(cmd == "build-road") {
    } else if (cmd == "build-res") {

    } else if (cmd == "improve") {
      string s;
      if(cin >> s) {
        istringstream(s) >> address;
        if(!properties.count(address)) {
          cout << "You cannot build here." << endl; // do not own
        } else if(!enoughResourcesToUpgrade(address)) {
          cout << "You do not have enough resources." << endl;
        } else {
          upgradeProperty(address);
        }
      } else {
        cout << "Invalid Command." << endl;
      }
    } else if (cmd == "trade") {
      string colour;
      string give;
      string take;
      if(cin >> colour >> give >> take) {

      } else {
        cout << "Invalid Command." << endl;
      }

    } else if(cmd == "help") {
      g->listCommands();
    } else if (cmd == "next") {
       break;
    } else if (cmd == "save") {
      string filename;
      if(cin >> filename) {
        g->saveGame(filename);
      } else {
        cout << "Invalid Command." << endl;
      }
    } else {
      cout << "Invalid Command." << endl;
    }
  }
}


string Player::getPlayerFirstLetter() {
  return colour.substr(0, 1);
}

void Player::setDiceToLoaded() {
  diceChosen = g->getLoadedDice();
}

void Player::setDiceToFair() {
  diceChosen = g->getFairDice();
}

bool Player::hasWon() {
  return numPoints >= 10;
}

ResourceType Player::getRandomResource() {
  int sumWeight = 0;
  for(auto i : resources) sumWeight += i;
  int randNum = g->genRand(1, sumWeight);
  // checks randNum against amount of each resource, returns if smaller
  // since porportional weight
  for(int i = 0; i < 6; ++i) { // hardcoded num resources
    if(randNum < resources[i]) {
      return static_cast<ResourceType>(i);
    } else {
      randNum -= resources[i];
    }
  }
}

string Player::save() {
  string saved;
  for(int i = 0; i < 6; ++i) {
    if(i) {
      saved += " ";
    }
    saved += resources[i];
  }
  saved += " r ";
  // loop through roads, add addressees
  saved += " h";
  for(auto const &address : properties) {
    saved += " " + address.second.lock()->getBuildingType();
  }
  return saved;
}

// SETTERS (for game file read in)
void Player::addProperty(int id, weak_ptr<Property> p) {
  properties[id] = p;
  PropertyType type = p.lock()->getPropertyType();
  if(type == PropertyType::Basement) {
    numPoints += 1;
  } else if(type == PropertyType::House) {
    numPoints += 2;
  } else { // tower
    numPoints += 3;
  }
}

// void Player::addRoad(int id, weak_ptr<Road> r) {  TODO: uncomment when roads implemented
//   roads[id] = r;
// }
//
void Player::setResources(const PlayerData & pd) {
  for(int i = 0; i < 6; ++i) {
    cout << "this resource value is" << pd.resources()[i] << endl;
  }
  resources = pd.resources();
}

bool Player::enoughResources(string p) {
  int len = Game::propertyRecipes.at(p).size(); // roads/props have diff lengths
  for(int i = 0; i < len; ++i) {
    if(Game::propertyRecipes.at(p)[i] > resources[i]) return false;
  }
  return true;
}

bool Player::enoughResourcesToUpgrade(int id) {
  PropertyType p = properties[id].lock()->getPropertyType();
  if(p == PropertyType::Basement) {
    return enoughResources("House");
  } else if (p == PropertyType::House) {
    return enoughResources("Tower");
  } else {
    return false;
  }
}

int Player::howManyResources(ResourceType r) {
  return resources[static_cast<int>(r)];
}

int Player::totalResources() {
  int total = 0;
  for(auto i : resources) total += i;
  return total;
}

int Player::totalChangeInResources() {
  int total = 0;
  for(auto i : changeInResources) total += i;
  return total;
}

void Player::subtractResource(ResourceType r, int qty) {
  resources[static_cast<int>(r)] -= qty;
  changeInResources[static_cast<int>(r)] -= qty;
}

string Player::getColour() const {
  return colour;
}

void Player::clearChangeInResources() {
  for(auto i : changeInResources) i = 0;
}
