#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "subject.h"
#include "subscriptions.h"
#include "resources.h"

class TextDisplay: public Observer {

  int m, n;
  std::vector<std::vector<char>> theDisplay;
  std::vector<std::string> a_prop;
  std::vector<std::string> a_road;
  std::vector<std::string> a_dv;
  std::vector<ResourceType> a_rt;
  std::vector<bool> a_geese;


public:
  TextDisplay();

  int getM() const;
  int getN() const;
  char getCharAt(int m, int n) const;

  void refresh();
  void insertAt(int i, int j, std::string s);
  void insertType(int i, int j, std::string s); 

  void notify(Subject &whoNotified) override;
  SubscriptionType subType() const override;

  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay& td);
};

#endif
