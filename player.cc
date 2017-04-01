#include "player.h"
#include "property.h"
#include "game.h"

using namespace std;

Player::Player(string colour, weak_ptr<Dice> diceChosen, Game * g):
colour{colour}, resources(6, 0), changeInResources(6, 0),
diceChosen{diceChosen}, g{g} {}

bool Player::buildProperty(int id) {
  // check if enough resources first, if not return false
  // converts shared ptr returned to weak_ptr
  weak_ptr<Property> w = g->getGameBoard()->buildProperty(id, shared_from_this());
  properties[id] = w;
  ++numPoints;
  cout << "buildProperty ran" << endl;
  return true;
}

void Player::addResource(ResourceType r, int qty) {
  resources[static_cast<int>(r)] += qty;
  changeInResources[static_cast<int>(r)] += qty;
  cout << "addedResource ran" << endl;
}



void Player::printStatus() {
  cout << colour << " has " << numPoints << " building points, " << resources[0] << " brick, " <<
    resources[1] << " energy, " << resources[2] << " glass, " << resources[3] <<
    " heat, and " << resources[4] <<" WiFi." << endl;

  printOwnedBuildings(); // TODO: REMOVE
 }

void Player::printOwnedBuildings() {
  cout << colour << " has built:" << endl;
  for(auto const &address : properties) {
    cout << to_string(address.first)  <<  " " << address.second.lock()->getBuildingType() <<  endl;
   }
}


bool Player::upgradeProperty(int id) {
   // if not enough resources, return false
   properties[id].lock()->upgrade();
   ++numPoints;
   cout << "upgradeProperty ran" << endl;
   return true;
 }

void Player::turn() {
  string cmd;
  int diceRoll;
  while(cin >> cmd) {
    if(cmd == "load") {
      setDiceToLoaded();
    } else if(cmd == "fair") {
      setDiceToFair();
    } else if (cmd == "roll") {
      diceRoll = diceChosen.lock()->getDiceRoll(cin, cout);
      cout << "You rolled a " << diceRoll << endl;
      g->getGameBoard()->getDiceRoll(diceRoll);
      // TODO: what each player gained, else no builders gained
      // for(int i = 0; i < 1; ++i) { // TODO: change to 4 when we finish
      //   g->getPlayer(i)->printGained();
      // }
      cout << "turn has completed" << endl;
      break; // exits loop once rolled
    } else {
      cout << "Invalid Command." << endl;
    }
   }

  int address;
  while(cin >> cmd) {
    if(cmd == "board") {

    } else if(cmd == "status") {
      for(int i = 0; i < 1; ++i) { // TODO: change to 4 when we finish
        g->getPlayer(i)->printStatus();
      }
    } else if(cmd == "residences") {
       printOwnedBuildings();
    } else if(cmd == "build-road") {
      if(cin >> address) {

      } else {
        cout << "Invalid Command." << endl;
      }
    } else if (cmd == "build-res") {
      if(cin >> address) {

      } else {
        cout << "Invalid Command." << endl;
      }
    } else if (cmd == "improve") {
      if(cin >> address) {

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
        //g->saveGame(filename); TODO: add when saveGame is updated
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

// dice functions
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
  int randNum = rand() % sumWeight + 1; // generate from 1 to total # // TODO: USE BOTTOM ONCE METHOD IS IN GAME
  // int randNum = g->genRand(1, sumWeight); // generate from 1 to total #
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
// void Player::setResources(const PlayerData & pd) { TODO: when player data added
//   resources = pd.resources();
// }

bool Player::enoughResources(string p) {
  for(int i = 0; i < 6; ++i) {
    if(Game::propertyRecipes.at(p)[i] > resources[i]) return false;
  }
  return true;
}

int Player::howManyResources(ResourceType r) {
  return resources[r];
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

void Player::addResource(ResourceType r, int qty) {
  resources[r] += qty;
  changeInResources[r] += qty;
}

void Player::subtractResource(ResourceType r, int qty) {
  resources[r] -= qty;
  changeInResources[r] -= qty;
}

void Player::getColour() {
  return colour;
}
