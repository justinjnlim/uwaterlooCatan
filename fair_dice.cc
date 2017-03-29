#include "fair_dice.h"

int FairDice::getDiceRoll(istream &in, ostream &out) {
  return dist(gen) + dist(gen);
}
