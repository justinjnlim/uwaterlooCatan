#include "observer.h"
#include "subject.h"
#include "subscriptions.h"

void Subject::attach(Observer *o) {
  observers.emplace_back(o);
}

void Subject::notifyObservers(SubscriptionType t) {
  for (auto ob : observers) { 
    if (ob->subType() == t) { 
      ob->notify(*this);
    }
  };
}

Subject::~Subject() {}
