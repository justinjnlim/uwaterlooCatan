#ifndef __TESTDISPLAY_H__
#define __TESTDISPLAY_H__
#include <iostream>
#include <vector>

class TestDisplay {
  std::vector<std::vector<char>> theDisplay;
  int m, n;
 public:
  TestDisplay(int m, int n);

  ~TestDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TestDisplay &td);
};

#endif
