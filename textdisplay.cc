#include <iostream>
#include <utility>
#include "textdisplay.h"
#include "cell.h"
#include "info.h"
using namespace std;

TextDisplay::TextDisplay() {}

void TextDisplay::notify(Subject &whoNotified) {
    Info cell = whoNotified.getInfo();
    if (cell.state) {
        theDisplay[cell.row][cell.col] = 'X';
    } else {
        theDisplay[cell.row][cell.col] = '_';
    }
}

TextDisplay::~TextDisplay() {}

SubscriptionType TextDisplay::subType() const {
    return SubscriptionType::All;
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
