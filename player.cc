#include "player.h"
#include "property.h"
#include "game.h"

using namespace std;

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

Player::Player(string colour, Game * g):colour{colour}, g{g} {}

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
  int diceRoll = 0;
  g->getGameBoard()->getDiceRoll(diceRoll);
  out << "turn has completed" << endl;
}
