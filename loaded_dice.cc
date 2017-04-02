#include <iostream>
#include <sstream>
#include "loaded_dice.h"
using namespace std;

int LoadedDice::getDiceRoll() {
  string s;
  cout << "Input a roll between 2 and 12:" << endl;
  cout << ">";

  while (cin >> s) {
    istringstream iss{s};
    int input;
    if (iss >> input && input > 1 && input < 13)
      return input;
    else {
      cout << "Invalid roll." << endl;
      cout << "Input a roll between 2 and 12:" << endl;
      cout << ">";
    }
  }
}

// int main() {
//   LoadedDice ld;
//   cout << ld.getDiceRoll(cin, cout) << endl;
// }
