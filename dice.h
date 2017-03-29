#ifndef _DICE_H_
#define _DICE_H_
#include <iostream>

class AbstractDice {
 public:
  virtual int getDiceRoll(std::istream &in, std::ostream &out) = 0;
};

#endif
