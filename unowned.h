#ifndef _UNOWNED_H_
#define _UNOWNED_H_
#include "property.h"
#include "resources.h"

class Unowned : public Property {

  void payOwner(ResourceType r);

};

#endif
