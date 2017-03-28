#include "fair_dice.h"

int FairDice::getDiceRoll() {
  return dist(gen) + dist(gen);
}
