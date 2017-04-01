#ifndef _FAIR_DICE_H_
#define _FAIR_DICE_H_
#include <iostream>
#include <random>
#include "dice.h"

class FairDice : public Dice {
 private:
  std::mt19937 gen; //{std::random_device{}()};
  std::uniform_int_distribution<> dist{1, 6};

 public:
  FairDice(std::mt19937 gen);
  int getDiceRoll(std::istream &in = std::cin, std::ostream &out = std::cout) override;
};

#endif
