#include <iostream>
#include <sstream>
#include "loaded_dice.h"
using namespace std;

int LoadedDice::getDiceRoll(istream &in, ostream &out) {
  string s;
  out << "Input a roll between 2 and 12:" << endl;

  while (in >> s) {
    istringstream ss{s}
    int input;
    if (ss >> input && input > 1 && input < 13)
      return input;
    else {
      out << "Invalid roll." << endl;
      out << "Input a roll between 2 and 12" << endl;
    }
  }
}
