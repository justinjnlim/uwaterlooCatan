#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <memory>
#include "subscriptions.h"
class Observer;

class Subject {
  std::vector<std::shared_ptr<Observer>> observers;
 public:
  void attach(std::shared_ptr<Observer> o);
  void notifyObservers(SubscriptionType t);
  virtual ~Subject() = 0;
};
#endif
