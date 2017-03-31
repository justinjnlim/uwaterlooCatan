#ifndef _TILEOBSERVER_H_
#define _TILEOBSERVER_H_
#include "subscriptions.h"
class TileSubject;

class TileObserver {
 public:
  virtual void notify(TileSubject &whoNotified) = 0;
  virtual SubscriptionType subType() const = 0;
  virtual ~TileObserver() = default;
};
#endif
