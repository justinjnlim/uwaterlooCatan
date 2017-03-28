#ifndef _HOUSE_H_
#define _HOUSE_H_
#include "property.h"
#include "resources.h"

class House : public Property {

  void payOwner(ResourceType r);

};

#endif
