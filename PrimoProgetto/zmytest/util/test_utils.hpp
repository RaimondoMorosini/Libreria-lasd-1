#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <cassert>
#include <string>
#include <iostream>
#include <typeinfo>
#include <stdexcept>

// ===================
// Macro di test
// ===================
#define ASSERT_EQ(x, y) assert((x) == (y))
#define ASSERT_TRUE(x)  assert(x)
#define ASSERT_FALSE(x) assert(!(x))
#define ASSERT_THROW(expr, exc_type)                        \
  try { expr; assert(false); } catch (const exc_type&) {}   \
  catch (...) { assert(false); }

// ===================
// Oggetto complesso
// ===================
struct MyObject {
  int id;
  std::string name;

  bool operator==(const MyObject& other) const {
    return id == other.id && name == other.name;
  }

  bool operator!=(const MyObject& other) const {
    return !(*this == other);
  }

  bool operator<(const MyObject& other) const {
    return id < other.id;
  }

  bool operator<=(const MyObject& other) const {
    return *this < other || *this == other;
  }

  bool operator>(const MyObject& other) const {
    return other < *this;
  }

  bool operator>=(const MyObject& other) const {
    return !(*this < other);
  }

  friend std::ostream& operator<<(std::ostream& os, const MyObject& obj) {
    os << "MyObject{id: " << obj.id << ", name: " << obj.name << "}";
    return os;
  }
};


// ===================
// MakeValue<T> 
// ===================
template <typename T>
T MakeValue(int i);

template <>
int MakeValue<int>(int i) { return i; }

template <>
std::string MakeValue<std::string>(int i) {
  return "str_" + std::to_string(i);
}

template <>
MyObject MakeValue<MyObject>(int i) {
  return MyObject{i, "obj_" + std::to_string(i)};
}

#endif // TEST_UTILS_HPP
