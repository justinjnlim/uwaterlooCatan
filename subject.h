#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <string>
#include <memory>
#include "info.h"
#include "subscriptions.h"
#include "resources.h"

class Observer;

class Subject {
  std::vector<std::shared_ptr<Observer>> observers;
 public:
  void attach(std::shared_ptr<Observer> o);
  void notifyObservers(SubscriptionType t);
  virtual Info getInfo() const = 0;

  virtual ~Subject() = 0;
};
#endif
