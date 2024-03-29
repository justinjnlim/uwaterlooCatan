#ifndef _PLAYER_DATA_H_
#define _PLAYER_DATA_H_
#include <string>
#include <vector>

class PlayerData {
 private:
  int playerPoints;
  std::vector<int> resourceCount; // {Bricks, Energy, Glass, Heat, Wifi}
  std::vector<int> roadIds;
  std::vector<int> basementIds;
  std::vector<int> houseIds;
  std::vector<int> towerIds;

 public:
  PlayerData(std::string loadString);
  int points();
  std::vector<int> resources();
  std::vector<int> roads();
  std::vector<int> basements();
  std::vector<int> houses();
  std::vector<int> towers();
};

#endif
