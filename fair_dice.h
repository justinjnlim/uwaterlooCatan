#ifndef _FAIR_DICE_H_
#define _FAIR_DICE_H_
#include <random>
#include "abstract_dice.h"

class FairDice : public AbstractDice {
 private:
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dist(1, 6);

 public:
  int getDiceRoll();
};

#endif
