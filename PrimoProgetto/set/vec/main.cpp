#include <iostream>
#include "setvec.hpp"
/*
g++-13 -Wall -pedantic -std=c++20 -MMD -MP -O3 -fsanitize=address main.cpp -o main
*/
using namespace std;
using namespace lasd;

int main() {
  cout << "SetVec<int> test" << endl;
  SetVec<int> s;

  cout << "Inserting 10, 5, 20, 15..." << endl;
  s.Insert(10);
  s.Insert(5);
  s.Insert(20);
  s.Insert(15);

  cout << "Elements in set (ordered): ";
  for (ulong i = 0; i < s.Size(); ++i) {
    cout << s[i] << " ";
  }
  cout << endl;

  cout << "Exists(15)? " << (s.Exists(15) ? "Yes" : "No") << endl;
  cout << "Remove(10)" << endl;
  s.Remove(10);

  cout << "Set after removal: ";
  for (ulong i = 0; i < s.Size(); ++i) {
    cout << s[i] << " ";
  }
  cout << endl;

  cout << "Min: " << s.Min() << ", Max: " << s.Max() << endl;

  cout << "RemoveMin(), RemoveMax()" << endl;
  s.RemoveMin();
  s.RemoveMax();

  cout << "Set after Min/Max removal: ";
  for (ulong i = 0; i < s.Size(); ++i)
  {
    cout << s[i] << " ";
  }
  cout << endl;

  s.Insert(12);
  s.Insert(18);
  cout << "Inserted 12, 18" << endl;

  cout << "Predecessor(15): " << s.Predecessor(15) << endl;
  cout << "Successor(12): " << s.Successor(12) << endl;

  cout << "Removing Predecessor(15)" << endl;
  s.RemovePredecessor(15);

  cout << "Set after RemovePredecessor(15): ";
  for (ulong i = 0; i < s.Size(); ++i)
  {
    cout << s[i] << " ";
  }
  cout << endl;

  cout << "Clear() set" << endl;
  s.Clear();
  cout << "Size after clear: " << s.Size() << endl;

  return 0;
}
