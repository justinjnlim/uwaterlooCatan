#ifndef _LOADED_DICE_H_
#define _LOADED_DICE_H_
#include "abstract_dice.h"

class LoadedDice : public AbstractDice {
 public:
  int getDiceRoll(std::istream &in, std::ostream &out);
};

#endif
