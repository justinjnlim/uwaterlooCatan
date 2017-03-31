#ifndef _BOARDOBSERVER_H_
#define _BOARDOBSERVER_H_
#include "subscriptions.h"
class BoardSubject;

class BoardObserver {
 public:
  virtual void notify(BoardSubject &whoNotified) = 0;
  virtual SubscriptionType subType() const = 0;
  virtual ~BoardObserver() = default;
};
#endif
