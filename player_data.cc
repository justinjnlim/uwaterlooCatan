#include <sstream>
#include <vector>
#include <iostream>
#include "player_data.h"
// #include <iostream>
using namespace std;

PlayerData::PlayerData(string loadString) {
  // playerPoints = 0;
  istringstream iss{loadString};
  string type;
  int num;
  while (iss >> num) { // count resources
    resourceCount.emplace_back(num);
  }
  iss.clear();

  iss >> type;
  if (type == "r") { // count roads if any
    while (iss >> num) {
      roadIds.emplace_back(num);
    }
    iss.clear();
    iss >> type; // read "h"
  }

  if (type == "h") {
    while (!iss.eof()) {
      iss >> num;
      iss >> type;

      switch (type[0]) {
      case 'B': // count basements if any
        basementIds.emplace_back(num);
        break;
      case 'H': // count houses if any
        houseIds.emplace_back(num);
        break;
      case 'T': // count towers if any
        towerIds.emplace_back(num);
        break;
      }

      // playerPoints++; // count points if any
    }
  }
}

// int PlayerData::points() {
//   return playerPoints;
// }

vector<int> PlayerData::resources() const {
  return resourceCount;
}

vector<int> PlayerData::roads() const {
  return roadIds;
}

vector<int> PlayerData::basements() const {
  return basementIds;
}

vector<int> PlayerData::houses() const {
  return houseIds;
}

vector<int> PlayerData::towers() const {
  return towerIds;
}

// int main() {
//   PlayerData pd("0 0 0 5 0 r 31 h 37 T 25 T 30 B 42 H");

//   cout << "Resources:" << endl;
//   cout << "Bricks " << pd.resources()[0] << endl;
//   cout << "Energy " << pd.resources()[1] << endl;
//   cout << "Glass " << pd.resources()[2] << endl;
//   cout << "Heat " << pd.resources()[3] << endl;
//   cout << "Wifi " << pd.resources()[4] << endl;

//   cout << "Roads:" << endl;
//   vector<int> r = pd.roads();
//   for (auto &it : r)
//     cout << it << endl;

//   cout << "Basements:" << endl;
//   auto b = pd.basements();
//   for (auto &it : b)
//     cout << it << endl;

//   cout << "Houses:" << endl;
//   auto h = pd.houses();
//   for (auto &it : h)
//     cout << it << endl;

//   cout << "Towers:" << endl;
//   auto t = pd.towers();
//   for (auto &it : t)
//     cout << it << endl;

//   cout << "Points: " << pd.points() << endl;
// }
