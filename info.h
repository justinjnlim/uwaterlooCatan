#ifndef __INFO_H__
#define __INFO_H__
#include "resources.h"

// Info struct for passing data from Subject to Observer
struct Info {
  int value;
  std::string type;
  bool hasGoose;
  std::string ownerString;
  ResourceType rt;
};

#endif
