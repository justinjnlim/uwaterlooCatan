#include <iostream>
#include <sstream>
#include "loaded_dice.h"
using namespace std;

int LoadedDice::getDiceRoll(istream &in, ostream &out) {
  string s;
  out << "Input a roll between 2 and 12:" << endl;

  while (in >> s) {
    istringstream iss{s};
    int input;
    if (iss >> input && input > 1 && input < 13)
      return input;
    else {
      out << "Invalid roll." << endl;
      out << "Input a roll between 2 and 12:" << endl;
    }
  }
}

// int main() {
//   LoadedDice ld;
//   cout << ld.getDiceRoll(cin, cout) << endl;
// }
