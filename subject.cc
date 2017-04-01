#include "subject.h"
#include "observer.h"
#include "subscriptions.h"

void Subject::attach(Observer *o) {
    observers.emplace_back(o);
}

void Subject::notifyObservers(SubscriptionType t) {
    for (auto ob : observers) { // iterate through observers
        if (ob->subType() == t) { // only notify the right subscribers
            ob->notify(*this);
        }
    };
}

Subject::~Subject() {}
