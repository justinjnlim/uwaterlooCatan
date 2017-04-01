#include "player.h"
#include "property.h"
#include "game.h"

using namespace std;

Player::Player(string colour, shared_ptr<Dice> diceChosen, Game * g):
colour{colour}, diceChosen{diceChosen}, g{g}, resources(6, 0),
changeInResources(6, 0) {}

bool Player::buildProperty(int id) {
  // check if enough resources first, if not return false
  shared_ptr<Property> p = g->getGameBoard()->buildProperty(id, shared_from_this());
  properties[id] = p;
  ++numPoints;
  cout << "buildProperty ran" << endl;
  return true;
}

void Player::addResource(ResourceType r, int qty) {
  resources[static_cast<int>(r)] += qty;
  changeInResources[static_cast<int>(r)] += qty;
  cout << "addedResource ran" << endl;
}



void Player::printStatus(ostream &out) {
  out << colour << " has " << numPoints << ", " << resources[0] << " brick, " <<
    resources[1] << " energy, " << resources[2] << " glass, " << resources[3] <<
    " heat, and " << resources[4] <<"WiFi." << endl;
  out << numPoints << " is my score" << endl;
 }

bool Player::upgradeProperty(int id) {
   // if not enough resources, return false
   properties[id]->upgrade();
   ++numPoints;
   cout << "upgradeProperty ran" << endl;
   return true;
 }

void Player::turn(istream &in, ostream &out) {
  int diceRoll = diceChosen->getDiceRoll(cin, cout);
  g->getGameBoard()->getDiceRoll(diceRoll);
  out << "turn has completed" << endl;
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
