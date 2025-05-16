@@ -1,168 +1,16 @@
#include <iostream>
#include <string>
#include "vector.hpp"

using namespace std;
using namespace lasd;

// Function to test Vector<int>
void testVectorInt() {
  cout << "\n\n=== Testing Vector<int> ===" << endl;

  // Test constructor with size
  cout << "\nCreating Vector with size 5..." << endl;
  Vector<int> vec(5);
  cout << "Vector size: " << vec.Size() << endl;
  
  // Test setting values
  cout << "\nSetting values..." << endl;
  try {
    vec[0] = 10;
    vec[1] = 20;
    vec[2] = 30;
    vec[3] = 40;
    vec[4] = 50;
    cout << "Values set successfully" << endl;
  } catch (const std::exception& e) {
    cout << "Error setting values: " << e.what() << endl;
  }

  // Test retrieving values
  cout << "\nRetrieving values:" << endl;
  try {
    cout << "vec[0] = " << vec[0] << endl;
    cout << "vec[1] = " << vec[1] << endl;
    cout << "vec[2] = " << vec[2] << endl;
    cout << "vec[3] = " << vec[3] << endl;
    cout << "vec[4] = " << vec[4] << endl;
    
    cout << "Front: " << vec.Front() << endl;
    cout << "Back: " << vec.Back() << endl;
  } catch (const std::exception& e) {
    cout << "Error retrieving values: " << e.what() << endl;
  }
  
  // Test out of range
  cout << "\nTesting out of range access:" << endl;
  try {
    cout << "Attempting to access vec[5]..." << endl;
    cout << vec[5] << endl;
  } catch (const std::exception& e) {
    cout << "Expected error: " << e.what() << endl;
  }

  // Test traversal
  cout << "\nTraversing vector:" << endl;
  vec.Traverse([](const int& val) { cout << val << " "; });
  cout << endl;
  
  // Test mapping
  cout << "\nMapping (multiplying each element by 2):" << endl;
  vec.Map([](int& val) { val *= 2; });
  vec.Traverse([](const int& val) { cout << val << " "; });
  cout << endl;
  
  // Test copy constructor
  cout << "\nTesting copy constructor:" << endl;
  Vector<int> vec2(vec);
  cout << "Original vector: ";
  vec.Traverse([](const int& val) { cout << val << " "; });
  cout << "\nCopied vector: ";
  vec2.Traverse([](const int& val) { cout << val << " "; });
  cout << endl;
  
  // Test comparison
  cout << "\nTesting comparison operators:" << endl;
  cout << "vec == vec2: " << (vec == vec2) << endl;
  
  // Modify vec2
  vec2[0] = 99;
  cout << "After modifying vec2[0] to 99:" << endl;
  cout << "vec == vec2: " << (vec == vec2) << endl;
  cout << "vec != vec2: " << (vec != vec2) << endl;
  
  // Test resize
  cout << "\nResizing vector from 5 to 3 elements:" << endl;
  vec.Resize(3);
  cout << "New size: " << vec.Size() << endl;
  cout << "Contents: ";
  vec.Traverse([](const int& val) { cout << val << " "; });
  cout << endl;
  
  // Test resize to larger
  cout << "\nResizing vector from 3 to 7 elements:" << endl;
  vec.Resize(7);
  cout << "New size: " << vec.Size() << endl;
  cout << "Contents: ";
  vec.Traverse([](const int& val) { cout << val << " "; });
  cout << endl;
  
  // Test clear
  cout << "\nClearing vector:" << endl;
  vec.Clear();
  cout << "Size after clear: " << vec.Size() << endl;
}

// Function to test SortableVector<int>
void testSortableVector() {
  cout << "\n\n=== Testing SortableVector<int> ===" << endl;
  
  SortableVector<int> vec(5);
  vec[0] = 30;
  vec[1] = 10;
  vec[2] = 50;
  vec[3] = 20;
  vec[4] = 40;
  
  cout << "\nBefore sorting: ";
  vec.Traverse([](const int& val) { cout << val << " "; });
  cout << endl;
  
  // Test sorting
  vec.Sort();
  
  cout << "After sorting: ";
  vec.Traverse([](const int& val) { cout << val << " "; });
  cout << endl;
}

// Function to test Vector<string>
void testVectorString() {
  cout << "\n\n=== Testing Vector<string> ===" << endl;
  
  Vector<string> vec(3);
  vec[0] = "Hello";
  vec[1] = "World";
  vec[2] = "C++";
  
  cout << "\nTraversing string vector:" << endl;
  vec.Traverse([](const string& val) { cout << val << " "; });
  cout << endl;
  
  // Map to uppercase
  cout << "\nMapping to uppercase:" << endl;
  vec.Map([](string& str) {
    for (char& c : str) {
      c = toupper(c);
    }
  });

  vec.Traverse([](const string& val) { cout << val << " "; });
  cout << endl;
}

int main() {
  cout << "=== Vector Implementation Test ===" << endl;
  
  try {
    testVectorInt();
    testSortableVector();
    testVectorString();
    
    cout << "\n\nAll tests completed successfully!" << endl;
  } catch (const std::exception& e) {
    cout << "\nTest failed with error: " << e.what() << endl;
  }
  
  return 0;
}