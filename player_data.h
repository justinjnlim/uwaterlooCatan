#ifndef _PLAYER_DATA_H_
#define _PLAYER_DATA_H_
#include <string>
#include <vector>

class PlayerData {
 private:
  /* int playerPoints; */
  std::vector<int> resourceCount; // {Bricks, Energy, Glass, Heat, Wifi}
  std::vector<int> roadIds;
  std::vector<int> basementIds;
  std::vector<int> houseIds;
  std::vector<int> towerIds;

 public:
  PlayerData(std::string loadString);
  /* int points(); */
  std::vector<int> resources() const;
  std::vector<int> roads() const;
  std::vector<int> basements() const;
  std::vector<int> houses() const;
  std::vector<int> towers() const;
};

#endif
