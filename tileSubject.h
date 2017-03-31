#ifndef _TILESUBJECT_H_
#define _TILESUBJECT_H_
#include <vector>
#include "subscriptions.h"
class TileObserver;

class TileSubject {
  std::vector<TileObserver**> observers;
 public:
  void attach(Observer **o);
  void notifyObservers(SubscriptionType t);
  virtual ~TileSubject() = 0;
};
