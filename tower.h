#ifndef _TOWER_H_
#define _TOWER_H_
#include "property.h"
#include "resources.h"

class Tower : public Property {

  void payOwner(ResourceType r);

};

#endif
