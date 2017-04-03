#ifndef _DICE_H_
#define _DICE_H_
#include <iostream>

class Dice {
 public:
  virtual int getDiceRoll() = 0;
  virtual std::string getType() = 0;
};

#endif
