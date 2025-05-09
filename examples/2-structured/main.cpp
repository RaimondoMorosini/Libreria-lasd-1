
#include <iostream>

#include "test.hpp"
// #include "test.hpp"

// #include "testx.hpp"

using namespace std;

// void testx() { cout << "# Other function" << endl; }; // cout << "";

int main() {
  cout << "Call to a function: # ";
  test();
  // testx();
  cout << " # Return from a function call!" << endl;
  cout << "Valore costante pi greco = " << pi << "..." << endl;
  return 0;
}
