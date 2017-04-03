#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "subscriptions.h"
class Subject;

// Observer for use in Observer design pattern
class Observer {
 public:
  virtual void notify(Subject &whoNotified) = 0;
  virtual SubscriptionType subType() const = 0;
  virtual ~Observer() = default;
};
#endif
