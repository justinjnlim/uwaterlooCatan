#include <iostream>
#include <utility>
#include "textdisplay.h"
#include "info.h"
using namespace std;


TextDisplay::TextDisplay(): m(41), n(54) theDisplay(m,vector<char>(n,' ')) {

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
      theDisplay[i][23] = '|';
      theDisplay[i][30] = '|';
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

void TextDisplay::refresh() {
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

void TextDisplay::insertAt(int i, int j, string s) {
  theDisplay[i][j] = s[0];
  theDisplay[i][j+1] = s[1];
}

void TextDisplay::notify(Subject &whoNotified) {
  Info cell = whoNotified.getInfo();
  if (cell.type == "Property") { 
    // Displays the new ownerString.
    a_prop[cell.value] = cell.ownerString;

  } else if (cell.type == "Road") {
    // Displays the new ownerString
    a_road[cell.value] = cell.ownerString;

  } else if (cell.type == "Tile") {

    

  }
  refresh();
}

TextDisplay::~TextDisplay() {}

SubscriptionType TextDisplay::subType() const {
  return SubscriptionType::Display;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (int r = 0; r < td.gridSize; ++r) {
    for (int c = 0; c < td.gridSize; ++c) {
      out << td.theDisplay[r][c];
    }
    out << endl;
  }
  return out;
}

int main() {

}
