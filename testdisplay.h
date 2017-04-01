#ifndef __TESTDISPLAY_H__
#define __TESTDISPLAY_H__
#include <iostream>
#include <vector>
#include <string>

class TestDisplay {
  std::vector<std::vector<char>> theDisplay;
  int m, n;
  std::vector<std::string> a_prop;
  std::vector<std::string> a_road;

 public:
  TestDisplay(int m, int n);

  void refresh();
  void insertAt(int i, int j, std::string s);
  void insertType(int i, int j, std::string s);

  ~TestDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TestDisplay &td);
};

#endif
