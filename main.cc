#include <fstream>
#include "game.h"
#include "property.h"
#include "board.h"
#include "player.h"
#include "tile.h"
using namespace std;

int main() {
  // cin.exceptions(istream::failbit|istream::eofbit|istream::badbit)
  // try
  //   bool stopGame = 1;
  //   while(stopGame)
  //     Game g
  //     check game flags -- call corresponding initializers
  //     stopGame = g.start();
  // catch (istream::failure & e)
  //   check istream.eof()
  //   g.save("backup.sv")

  Game g;
  ifstream f{"provided_files/savefile.txt"};
  g.load(f);
  g.start();
}
