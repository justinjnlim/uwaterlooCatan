#include <iostream>
#include <utility>
#include "testdisplay.h"
//#include "info.h"

using namespace std;

TestDisplay::TestDisplay(int m, int n): theDisplay(m,vector<char>(n,' ')), m(m), n(n) {

  for (int i = 0; i < 54; ++i) {
    if (i < 10) {
      a_prop.emplace_back(" " + to_string(i));
    } else {
      a_prop.emplace_back(to_string(i));
    }
  }

  for (int i = 0; i < 72; ++i) {
    if (i < 10) {
      a_road.emplace_back(" " + to_string(i));
    } else {
      a_road.emplace_back(to_string(i)); 
    }
  }

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

      insertAt(i,21,"AB");

      theDisplay[i][23] = '|';
      theDisplay[i][30] = '|';

      insertAt(i,31,"CD");

      theDisplay[i][33] = '|';
      if (i > 0 && i < 40) {
        theDisplay[i][10] = '|';

        insertAt(i,11,"EF");

        theDisplay[i][13] = '|';
        theDisplay[i][40] = '|';

        insertAt(i,41,"GH");

        theDisplay[i][43] = '|';
        if (i > 4 && i < 36) {
          theDisplay[i][0] = '|';

          insertAt(i,1,"IJ");

          theDisplay[i][3] = '|';
          theDisplay[i][50] = '|';

          insertAt(i,51,"KL");

          theDisplay[i][53] = '|';
        }
      }
    }

    if (i % 8 == 0) {
      theDisplay[i][24] = '-';
      theDisplay[i][25] = '-';

      insertAt(i,26,"12");

      theDisplay[i][28] = '-';
      theDisplay[i][29] = '-';
      if (i > 0 && i < 40) {
        theDisplay[i][4] = '-';
        theDisplay[i][5] = '-';

        insertAt(i,6,"78");

        theDisplay[i][8] = '-';
        theDisplay[i][9] = '-';
        theDisplay[i][44] = '-';
        theDisplay[i][45] = '-';

        insertAt(i,46,"90");

        theDisplay[i][48] = '-';
        theDisplay[i][49] = '-';
      }
    }

    if ((i-4) % 8 == 0) {
      theDisplay[i][14] = '-';
      theDisplay[i][15] = '-';

      insertAt(i,16,"34");

      theDisplay[i][18] = '-';
      theDisplay[i][19] = '-';
      theDisplay[i][34] = '-';
      theDisplay[i][35] = '-';

      insertAt(i,36,"56");

      theDisplay[i][38] = '-';
      theDisplay[i][39] = '-';
    }
  }
}

void TestDisplay::refresh() {
  int p = 0, r = 0;

  for (int i = 0; i < m; ++i) {

    if (i % 4 == 0) {
      if (i > 4 && i < 36) insertAt(i,1,a_prop[p++]);
      if (i % 8 == 0 && i > 0 && i < 40) insertAt(i,6,a_road[r++]);
      if (i > 0 && i < 40) insertAt(i,11,a_prop[p++]);

      if ((i-4) % 8 == 0) insertAt(i,16,a_road[r++]);
      insertAt(i,21,a_prop[p++]);
      if (i % 8 == 0) insertAt(i,26,a_road[r++]);
      insertAt(i,31,a_prop[p++]);
      if ((i-4) % 8 == 0) insertAt(i,36,a_road[r++]);

      if (i > 0 && i < 40) insertAt(i,41,a_prop[p++]);
      if (i % 8 == 0 && i > 0 && i < 40) insertAt(i,46,a_road[r++]);

      if (i > 4 && i < 36) insertAt(i,51,a_prop[p++]);
    }

    if ((i + 2) % 4 == 0 && i > 0 && i < 40) {
      if (i > 8 && i < 32) insertAt(i,1,a_road[r++]);
      if (i > 4 && i < 36) insertAt(i,11,a_road[r++]);
      insertAt(i,21,a_road[r++]);
      insertAt(i,31,a_road[r++]);
      if (i > 4 && i < 36) insertAt(i,41,a_road[r++]);
      if (i > 8 && i < 32) insertAt(i,51,a_road[r++]);
    }
  }
}

void TestDisplay::insertAt(int i, int j, string s) {
  theDisplay[i][j] = s[0];
  theDisplay[i][j+1] = s[1];
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

  // filling in properties
  td.refresh();


  cout << td;

}
