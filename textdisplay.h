#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "subject.h"
#include "subscriptions.h"

class TextDisplay: public Observer {
  // a map of type to id to location on grid?
  std::vector<string> tiles;
  std::vector<string> roads;
  std::vector<string> properties;

  std::vector<std::vector<char>> theDisplay;

public:
  TextDisplay();

  void notify(Subject &whoNotified) override;
  SubscriptionType subType() const override;

  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
