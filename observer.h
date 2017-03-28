#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "subscriptions.h"
class Subject;

class Observer {
 public:
  virtual void notify(Subject &whoNotified) = 0;
  virtual SubscriptionType subType() const = 0;
  virtual ~Observer() = default;
};
#endif
