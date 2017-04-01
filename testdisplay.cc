#include <iostream>
#include <utility>
#include "testdisplay.h"
//#include "info.h"

using namespace std;

TestDisplay::TestDisplay(int m, int n): theDisplay(m,vector<char>(n,' ')), m(m), n(n), names(53) {

  for (int i = 0; i < 53; ++i) {
    names[i] = to_string(i);
  }
  int k = 0;

  for (int i = 0; i < m; ++i) {

    if (i % 2 == 1) {
      theDisplay[i][22] = '|';
      theDisplay[i][32] = '|';
      if (i > 4 && i < 36) {
        theDisplay[i][12] = '|';
        theDisplay[i][42] = '|';
        if (i > 8 && i < 32) {
          theDisplay[i][2] = '|';
          theDisplay[i][52] = '|';
        }
      }
    }

    if (i % 4 == 0) {
      theDisplay[i][20] = '|';

      // CREATE A METHOD FOE THIS KIND OF THING
      if (stoi(names[k]) > 9) {
        theDisplay[i][21] = names[k++][0];
        theDisplay[i][22] = names[k++][1];
      } else {
        theDisplay[i][22] = names[k++][0];
      }

      theDisplay[i][23] = '|';
      theDisplay[i][30] = '|';

      if (stoi(names[k]) > 9) {
        theDisplay[i][31] = names[k++][0];
        theDisplay[i][32] = names[k++][1];
      } else {
        theDisplay[i][32] = names[k++][0];
      }

      theDisplay[i][33] = '|';
      if (i > 0 && i < 40) {
        theDisplay[i][10] = '|';
        theDisplay[i][13] = '|';
        theDisplay[i][40] = '|';
        theDisplay[i][43] = '|';
        if (i > 4 && i < 36) {
          theDisplay[i][0] = '|';
          theDisplay[i][3] = '|';
          theDisplay[i][50] = '|';
          theDisplay[i][53] = '|';
        }
      }
    }

    if (i % 8 == 0) {
      theDisplay[i][24] = '-';
      theDisplay[i][25] = '-';
      theDisplay[i][28] = '-';
      theDisplay[i][29] = '-';
      if (i > 0 && i < 40) {
        theDisplay[i][4] = '-';
        theDisplay[i][5] = '-';

        theDisplay[i][8] = '-';
        theDisplay[i][9] = '-';
        theDisplay[i][44] = '-';
        theDisplay[i][45] = '-';

        theDisplay[i][48] = '-';
        theDisplay[i][49] = '-';
      }
    }

    if ((i-4) % 8 == 0) {
      theDisplay[i][14] = '-';
      theDisplay[i][15] = '-';
      theDisplay[i][18] = '-';
      theDisplay[i][19] = '-';
      theDisplay[i][34] = '-';
      theDisplay[i][35] = '-';
      theDisplay[i][38] = '-';
      theDisplay[i][39] = '-';
    }
  }
}

TestDisplay::~TestDisplay() {}

ostream &operator<<(ostream &out, const TestDisplay &td) {
  for (int r = 0; r < td.m; ++r) {
    for (int c = 0; c < td.n; ++c) {
      out << td.theDisplay[r][c];
    }
    out << endl;
  }
  return out;
}

int main() {

  TestDisplay td(41,54);
  cout << td;

}
