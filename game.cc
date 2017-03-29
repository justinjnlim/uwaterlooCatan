#include <iostream>
#include "game.h"
using namespace std;

map<string, string> Game::createPropRecipes() {
  map<string, string> m;
  m["Basement"] = "Brick 1 Energy 1 Glass 1 Wifi 1";
  m["House"] = "Glass 2 Heat 3";
  m["Tower"] = "Brick 3 Energy 2 Glass 2 Wifi 1 Heat 2";
  return m;
}

const map<string, string> Game::propertyRecipes = Game::createPropRecipes();
