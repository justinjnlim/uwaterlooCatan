#include <fstream>
#include <iostream>
#include <getopt.h>
#include <stdexcept>
#include "game.h"
#include "property.h"
#include "board.h"
#include "player.h"
#include "tile.h"
using namespace std;

struct gameOptions {
  bool loadFlag = 0;
  bool boardFlag = 0;
  bool randomFlag = 0;
  int seed = 1;
  string loadFile;
  string boardFile;
};

void errorMessage() {
  cout << "Ctor game parameters not provided. Available options are:\n" << endl;
  cout << "--seed         [-s] xxx : Set seed for random generator to xxx" << endl;
  cout << "--load         [-l] xxx : Load game from xxx" << endl;
  cout << "--board        [-b] xxx : Load board layout from xxx" << endl;
  cout << "--random-board [-r]     : Generate random board" << endl;
}

int main(int argc, char * argv[]) {
  if (argc <= 1) {
    errorMessage();
    return 1;
  }

  static struct option long_options[] = {
    {"seed",          required_argument, 0, 's' },
    {"load",          required_argument, 0, 'l' },
    {"board",         required_argument, 0, 'b' },
    {"random-board",  no_argument,       0, 'r' },
    {0,               0,                 0,  0  }
  };

  gameOptions options;
  int index;
  int iarg = 0;

  while (iarg != -1) {
    iarg = getopt_long(argc, argv, "s:l:b:r", long_options, &index);

    switch (iarg) {
    case 's':
      options.seed = stoi(optarg);
      break;
    case 'l':
      options.loadFlag = 1;
      options.loadFile = optarg;
      break;
    case 'b':
      options.boardFlag = 1;
      options.boardFile = optarg;
      break;
    case 'r':
      options.randomFlag = 1;
      break;
    }
  }

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
  try {
    bool stopGame = 1;
    while (stopGame) {
      Game g(options.seed);

      if (options.loadFlag) {
        options.boardFlag = 0;
        options.randomFlag = 0;

        ifstream f{options.loadFile};
        g.load(f);
      }

      if (options.boardFlag) {
        options.randomFlag = 0;

        ifstream f{options.boardFile};
        g.setGameBoard(f);
      }

      if (options.randomFlag) {
        g.setGameBoard();
      }

      stopGame = g.start();
    }
  } catch (exception & e) {
    cout << "Error: " << e.what() << endl;
    cout << "Terminating..." << endl;
  }
}
