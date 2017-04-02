#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "subject.h"
#include "subscriptions.h"

class TextDisplay: public Observer {

  int m, n;
  std::vector<std::vector<char>> theDisplay;
  std::vector<std::string> a_prop;
  std::vector<std::string> a_road;
  std::vector<std::string> a_tile;;

public:
  TextDisplay();

  void refresh();
  void insertAt(int i, int j, std::string s);
  void insertType(int i, int j, std::string s); 

  void notify(Subject &whoNotified) override;
  SubscriptionType subType() const override;

  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
