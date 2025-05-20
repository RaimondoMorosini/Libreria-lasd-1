#ifndef TEST_VECTOR_HPP
#define TEST_VECTOR_HPP

#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "../util/test_utils.hpp" // per ASSERT_EQ ecc
#include "../../vector/vector.hpp"

using namespace std;
using namespace lasd;

// Test generico Vector<T>
template <typename T>
void TestVector() {
  cout << "\n=== Testing Vector<" << typeid(T).name() << "> ===" << endl;

  Vector<T> vec(5);
  ASSERT_EQ(vec.Size(), 5);

  // Set values
  for (unsigned i = 0; i < vec.Size(); ++i) {
    vec[i] = MakeValue<T>(static_cast<int>(i + 1));
  }

  // Check values
  for (unsigned i = 0; i < vec.Size(); ++i) {
    ASSERT_EQ(vec[i], MakeValue<T>(static_cast<int>(i + 1)));
  }

  // Front and Back
  ASSERT_EQ(vec.Front(), MakeValue<T>(1));
  ASSERT_EQ(vec.Back(), MakeValue<T>(5));

  // Out of range access
  try {
    auto x = vec[vec.Size()]; // Access out of bounds
    (void)x;
    assert(false && "Expected out_of_range exception");
  } catch (const std::out_of_range&) {}

  // Traverse: just print values  
  cout << "Traverse: ";
  vec.Traverse([](const T& val) { cout << val << " "; });
  cout << endl;

  // Map: multiply by 2 if numeric, else leave unchanged
  vec.Map([](T& val) {
    if constexpr (std::is_integral_v<T>) {
      val = val * 2;
    }
  });

  // Check mapped values if integral
  if constexpr (std::is_integral_v<T>) {
    for (unsigned i = 0; i < vec.Size(); ++i) {
      ASSERT_EQ(vec[i], MakeValue<T>(static_cast<int>((i + 1) * 2)));
    }
  }

  // Copy constructor
  Vector<T> vec2(vec);
  ASSERT_EQ(vec, vec2);

  // Modify vec2 and test comparison
  if constexpr (std::is_integral_v<T>) {
    vec2[0] = MakeValue<T>(999);
  } else {
    vec2[0] = MakeValue<T>(-1); // fallback for non-integral (may not make sense)
  }

  ASSERT_TRUE(vec != vec2);

  // Resize smaller
  vec.Resize(3);
  ASSERT_EQ(vec.Size(), 3);

  // Resize larger (new elements default constructed)
  vec.Resize(7);
  ASSERT_EQ(vec.Size(), 7);

  // Clear
  vec.Clear();
  ASSERT_EQ(vec.Size(), 0);

  cout << "All tests passed for Vector<" << typeid(T).name() << ">." << endl;
}

// Test SortableVector<int>
inline void TestSortableVectorInt() {
  cout << "\n=== Testing SortableVector<int> ===" << endl;
  SortableVector<int> vec(5);
  vec[0] = 30;
  vec[1] = 10;
  vec[2] = 50;
  vec[3] = 20;
  vec[4] = 40;

  cout << "Before sorting: ";
  vec.Traverse([](const int& val) { cout << val << " "; });
  cout << endl;

  vec.Sort();

  cout << "After sorting: ";
  vec.Traverse([](const int& val) { cout << val << " "; });
  cout << endl;

  // Check sorted order
  for (unsigned i = 1; i < vec.Size(); ++i) {
    ASSERT_TRUE(vec[i-1] <= vec[i]);
  }

  cout << "All tests passed for SortableVector<int>." << endl;
}

// Special test for Vector<string>
inline void TestVectorString() {
  cout << "\n=== Testing Vector<string> specific ===" << endl;
  Vector<string> vec(3);
  vec[0] = "Hello";
  vec[1] = "World";
  vec[2] = "C++";

  cout << "Original: ";
  vec.Traverse([](const string& val) { cout << val << " "; });
  cout << endl;

  // Map to uppercase
  vec.Map([](string& s) {
    for (char& c : s) {
      c = static_cast<char>(toupper(c));
    }
  });

  cout << "Uppercase: ";
  vec.Traverse([](const string& val) { cout << val << " "; });
  cout << endl;

  // Check uppercase
  ASSERT_EQ(vec[0], "HELLO");
  ASSERT_EQ(vec[1], "WORLD");
  ASSERT_EQ(vec[2], "C++");

  cout << "All tests passed for Vector<string> specific." << endl;
}

#endif // TEST_VECTOR_HPP
