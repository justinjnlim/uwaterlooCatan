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
  cout << colour << " has built:" << endl;

  // remove this later
  printOwnedBuildings();
 }

 void Player::printOwnedBuildings() {
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
      cout << "turn has completed" << endl;
      break; // exits loop once rolled
    } else {
      cout << "Invalid Command." << endl;
    }
   }

   while(cin >> cmd) {
     if(cmd == "status") {
       for(int i = 0; i < 1; ++i) { // TODO: hardcoded NUM OF PLAYERS MIGHT WANNA CHANGE
         g->getPlayer(i)->printStatus();
       }
     } else if(cmd == "help") {
       g->listCommands();
     } else if (cmd == "next") {
       break;
     } else {
       cout << "Invalid Command." << endl;
     }
   }
}

string Player::getPlayerFirstLetter() {
  return colour.substr(0, 1);
}

// SETTERS/GETTERS

// void Player::setPoints(int p) {
//   numPoints = p;
// }
//
// void Player::addProperty(int id, shared_ptr<Property> p) { // check if still shared ptr
//   properties[id] = p;
//   numPoints += 1;
// }
//
// // void Player::addRoad(shared_ptr<Road> r) {
// //   roads[id] = r;
// // }
//
// void Player::setDice(Dice * d) {
//   diceChosen = d;
// }
//
// void Player::setGame(Game * game) {
//   g = game;
// }

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

g->genRand(x, y)
