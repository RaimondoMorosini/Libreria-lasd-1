#include <iostream>
#include <string>
#include <stdexcept>
#include <random>
#include "../vector/vector.hpp"

/* ************************************************************************** */

using namespace std;
using namespace lasd;

/* ************************************************************************** */

// Utility functions
template <typename Data>
void PrintTestHeader(const string& testName) {
  cout << "\n\n==== Testing " << testName << " ====" << endl;
}

template <typename Data>
void PrintVector(const Vector<Data>& vec, const string& label) {
  cout << label << " (size " << vec.Size() << "): ";
  vec.Traverse([](const Data& val) { cout << val << " "; });
  cout << endl;
}

// Test Vector Construction
void TestVectorConstruction() {
  PrintTestHeader<int>("Vector Construction");
  
  // Default constructor
  cout << "Testing default constructor..." << endl;
  Vector<int> vec1;
  cout << "Default vector size: " << vec1.Size() << endl;
  cout << "Is empty? " << (vec1.Empty() ? "Yes" : "No") << endl;
  
  // Size constructor
  cout << "\nTesting size constructor..." << endl;
  Vector<int> vec2(5);
  cout << "Vector with size 5 - size: " << vec2.Size() << endl;
  cout << "Is empty? " << (vec2.Empty() ? "Yes" : "No") << endl;
  
  // Fill vector with values
  for(unsigned long i = 0; i < vec2.Size(); i++) {
    vec2[i] = i * 10;
  }
  PrintVector(vec2, "Vector after filling");
  
  // Copy constructor
  cout << "\nTesting copy constructor..." << endl;
  Vector<int> vec3(vec2);
  PrintVector(vec3, "Copied vector");
  
  // Check independence
  vec2[0] = 999;
  cout << "After modifying original vector[0] to 999:" << endl;
  PrintVector(vec2, "Original vector");
  PrintVector(vec3, "Copied vector (should be unchanged)");
  
  // Move constructor
  cout << "\nTesting move constructor..." << endl;
  Vector<int> vec4(std::move(vec3));
  PrintVector(vec4, "Moved vector");
  cout << "Original vector after move - size: " << vec3.Size() << endl;
}

// Test Basic Vector Operations
void TestVectorBasicOperations() {
  PrintTestHeader<int>("Basic Vector Operations");
  
  Vector<int> vec(5);
  for(unsigned long i = 0; i < vec.Size(); i++) {
    vec[i] = (i + 1) * 10;
  }
  PrintVector(vec, "Test vector");
  
  // Test operator[]
  cout << "\nTesting operator[]..." << endl;
  cout << "vec[0]: " << vec[0] << endl;
  cout << "vec[2]: " << vec[2] << endl;
  cout << "vec[4]: " << vec[4] << endl;
  
  // Test Front and Back
  cout << "\nTesting Front() and Back()..." << endl;
  cout << "Front: " << vec.Front() << endl;
  cout << "Back: " << vec.Back() << endl;
  
  // Test modification using operator[]
  cout << "\nModifying elements..." << endl;
  vec[0] = 100;
  vec[4] = 500;
  PrintVector(vec, "After modification");
  
  // Test Front and Back modification
  cout << "\nModifying Front and Back..." << endl;
  vec.Front() = 111;
  vec.Back() = 555;
  PrintVector(vec, "After Front/Back modification");
  
  // Test error handling
  cout << "\nTesting error handling..." << endl;
  try {
    cout << "Attempting to access out of bounds: vec[10]..." << endl;
    cout << vec[10] << endl;
  } catch (const std::exception& e) {
    cout << "Caught expected exception: " << e.what() << endl;
  }
  
  // Test empty vector error handling
  Vector<int> emptyVec;
  try {
    cout << "\nAttempting to access Front() of empty vector..." << endl;
    cout << emptyVec.Front() << endl;
  } catch (const std::exception& e) {
    cout << "Caught expected exception: " << e.what() << endl;
  }
  
  try {
    cout << "\nAttempting to access Back() of empty vector..." << endl;
    cout << emptyVec.Back() << endl;
  } catch (const std::exception& e) {
    cout << "Caught expected exception: " << e.what() << endl;
  }
}

// Test Vector Resizing
void TestVectorResizing() {
  PrintTestHeader<int>("Vector Resizing");
  
  Vector<int> vec(3);
  vec[0] = 10;
  vec[1] = 20;
  vec[2] = 30;
  PrintVector(vec, "Original vector");
  
  // Resize to larger
  cout << "\nResizing to larger (5 elements)..." << endl;
  vec.Resize(5);
  PrintVector(vec, "After resize to 5");
  
  // Add values to new elements
  vec[3] = 40;
  vec[4] = 50;
  PrintVector(vec, "After filling new elements");
  
  // Resize to smaller
  cout << "\nResizing to smaller (2 elements)..." << endl;
  vec.Resize(2);
  PrintVector(vec, "After resize to 2");
  
  // Resize to zero
  cout << "\nResizing to zero..." << endl;
  vec.Resize(0);
  cout << "Size after resizing to 0: " << vec.Size() << endl;
  cout << "Is empty? " << (vec.Empty() ? "Yes" : "No") << endl;
  
  // Test Clear
  Vector<int> vec2(3);
  vec2[0] = 100;
  vec2[1] = 200;
  vec2[2] = 300;
  PrintVector(vec2, "New vector before Clear");
  
  cout << "\nClearing vector..." << endl;
  vec2.Clear();
  cout << "Size after Clear: " << vec2.Size() << endl;
  cout << "Is empty? " << (vec2.Empty() ? "Yes" : "No") << endl;
}

// Test Traversal and Mapping
void TestTraversalAndMapping() {
  PrintTestHeader<int>("Traversal and Mapping");
  
  Vector<int> vec(5);
  for(unsigned long i = 0; i < vec.Size(); i++) {
    vec[i] = i + 1;  // 1, 2, 3, 4, 5
  }
  PrintVector(vec, "Original vector");
  
  // Test traversal
  cout << "\nTesting Traverse..." << endl;
  cout << "Elements: ";
  vec.Traverse([](const int& val) { cout << val << " "; });
  cout << endl;
  
  // Test PreOrderTraverse (same as Traverse for Vector)
  cout << "\nTesting PreOrderTraverse..." << endl;
  cout << "Elements: ";
  vec.PreOrderTraverse([](const int& val) { cout << val << " "; });
  cout << endl;
  
  // Test PostOrderTraverse (same as Traverse for Vector)
  cout << "\nTesting PostOrderTraverse..." << endl;
  cout << "Elements: ";
  vec.PostOrderTraverse([](const int& val) { cout << val << " "; });
  cout << endl;
  
  // Test mapping (multiply each element by 2)
  cout << "\nTesting Map (multiply each element by 2)..." << endl;
  vec.Map([](int& val) { val *= 2; });
  PrintVector(vec, "After Map");
  
  // Test PreOrderMap
  cout << "\nTesting PreOrderMap (add 5 to each element)..." << endl;
  vec.PreOrderMap([](int& val) { val += 5; });
  PrintVector(vec, "After PreOrderMap");
  
  // Test PostOrderMap
  cout << "\nTesting PostOrderMap (subtract 1 from each element)..." << endl;
  vec.PostOrderMap([](int& val) { val -= 1; });
  PrintVector(vec, "After PostOrderMap");
  
  // Test with string Vector
  cout << "\nTesting with string Vector..." << endl;
  Vector<string> strVec(3);
  strVec[0] = "hello";
  strVec[1] = "world";
  strVec[2] = "vector";
  PrintVector(strVec, "String vector");
  
  // Map to uppercase
  cout << "\nMapping strings to uppercase..." << endl;
  strVec.Map([](string& s) {
    for(char& c : s) {
      c = toupper(c);
    }
  });
  PrintVector(strVec, "After uppercase mapping");
}

// Test SortableVector
void TestSortableVector() {
  PrintTestHeader<int>("SortableVector");
  
  // Create and fill SortableVector with random values
  SortableVector<int> vec(10);
  
  // Use random generator for test values
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 100);
  
  for(unsigned long i = 0; i < vec.Size(); i++) {
    vec[i] = distrib(gen);
  }
  PrintVector(vec, "Unsorted vector");
  
  // Sort the vector
  cout << "\nSorting vector..." << endl;
  vec.Sort();
  PrintVector(vec, "Sorted vector");
  
  // Verify sorting
  bool isSorted = true;
  for(unsigned long i = 1; i < vec.Size(); i++) {
    if(vec[i] < vec[i-1]) {
      isSorted = false;
      break;
    }
  }
  cout << "Vector is " << (isSorted ? "correctly" : "NOT correctly") << " sorted" << endl;
  
  // Test with string SortableVector
  cout << "\nTesting SortableVector with strings..." << endl;
  SortableVector<string> strVec(5);
  strVec[0] = "zebra";
  strVec[1] = "apple";
  strVec[2] = "orange";
  strVec[3] = "banana";
  strVec[4] = "kiwi";
  PrintVector(strVec, "Unsorted string vector");
  
  cout << "\nSorting string vector..." << endl;
  strVec.Sort();
  PrintVector(strVec, "Sorted string vector");
}

// Main test function
void mytest() {
  cout << "\n\n*** MY VECTOR TEST SUITE ***\n" << endl;
  
  try {
    TestVectorConstruction();
    TestVectorBasicOperations();
    TestVectorResizing();
    TestTraversalAndMapping();
    TestSortableVector();
    
    cout << "\n\n*** ALL TESTS COMPLETED SUCCESSFULLY ***" << endl;
  } catch(const std::exception& e) {
    cout << "\n\nTEST FAILED: " << e.what() << endl;
  }
}
