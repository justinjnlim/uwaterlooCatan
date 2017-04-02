#include <iostream>
#include <exception>
using namespace std;

int main() {
  string s;
  cin.exceptions(istream::failbit|istream::eofbit|istream::badbit);

  try {
    while (cin >> s)
      cout << "Printed: " << s << endl;
  } catch (istream::failure & e) {
    cout << "Failed on: " << e.what() << endl;
    cout << "Error bits are: "
         << "\nfailbit: " << cin.fail() 
         << "\neofbit: " << cin.eof()
         << "\nbadbit: " << cin.bad() << endl;   
  }
}
