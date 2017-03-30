#include <iostream>
#include "fair_dice.h"
using namespace std;

int FairDice::getDiceRoll(istream &in, ostream &out) {
  return dist(gen) + dist(gen);
}

// int main() {
//   FairDice fd;
//   cout << fd.getDiceRoll(cin, cout) << endl;
// }
