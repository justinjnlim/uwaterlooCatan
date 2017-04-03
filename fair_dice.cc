#include "fair_dice.h"
using namespace std;

FairDice::FairDice(mt19937 gen): gen{gen} {};

int FairDice::getDiceRoll() {
  return dist(gen) + dist(gen);
}

string FairDice::getType() {
  return "Fair Dice";
}

// int main() {
//   FairDice fd(seed);
//   for (int i = 0; i < 10; i++)
//     cout << fd.getDiceRoll(cin, cout) << endl;
// }
