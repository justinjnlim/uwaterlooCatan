#ifndef _DICE_H_
#define _DICE_H_
#include <iostream>

class AbstractDice {
 public:
  virtual int getDiceRoll(istream &in, ostream &out) = 0;
};

#endif
