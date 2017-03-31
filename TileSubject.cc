#include "tileObserver.h"
#include "tileSubject.h"
#include "subscriptions.h"

void TileSubject::attach(TileObserver** o) {
  observers.emplace_back(o);
}

void TileSubject::notifyObservers(SubscriptionType t) {
  for (auto ob : observers) { 
    if (ob->subType() == t) { 
      (*ob)->notify(*this);
    }
  };
}

TileSubject::~TileSubject() {}
