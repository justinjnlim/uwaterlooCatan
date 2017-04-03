#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "subject.h"
#include "subscriptions.h"
#include "resources.h"

// Displays the state of the board in a text-based format
class TextDisplay: public Observer {

  int m, n;
  std::vector<std::vector<char>> theDisplay;
  std::vector<std::string> a_prop;
  std::vector<std::string> a_road;
  std::vector<std::string> a_tile;
  std::vector<std::string> a_dv;
  std::vector<ResourceType> a_rt;
  std::vector<bool> a_geese;

private:
  // internal setters
  void refresh();
  void insertAt(int i, int j, std::string s);
  void insertResource(int i, int j, ResourceType rt); 
  void insertGoose(int i, int j, bool hasGoose);

public:
  TextDisplay();
  
  // Getters
  int getM() const;
  int getN() const;
  char getCharAt(int m, int n) const;

  // Observer overrides; notify updates the board state of given subject
  void notify(Subject &whoNotified) override;
  SubscriptionType subType() const override;

  ~TextDisplay();

  // overload output operator
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay& td);
};

#endif
