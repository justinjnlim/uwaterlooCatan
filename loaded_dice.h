#ifndef _LOADED_DICE_H_
#define _LOADED_DICE_H_
#include "dice.h"

class LoadedDice : public AbstractDice {
 public:
  int getDiceRoll(std::istream &in, std::ostream &out) override;
};

#endif
