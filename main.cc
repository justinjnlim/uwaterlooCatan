#include <fstream>
#include "game.h"
#include "property.h"
#include "board.h"
#include "player.h"
#include "tile.h"
using namespace std;

int main() {

  Game g;
  ifstream f{"provided_files/savefile.txt"};
  g.loadGame(f);

  g.startGame();
}
