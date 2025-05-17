#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include "setvec.hpp"

using namespace lasd;

// ===== Helper macro =====
#define ASSERT_EQ(x, y) assert((x) == (y))
#define ASSERT_TRUE(x)  assert(x)
#define ASSERT_FALSE(x) assert(!(x))
#define ASSERT_THROW(expr, exc_type)                        \
  try { expr; assert(false); } catch (const exc_type&) {}   \
  catch (...) { assert(false); }

// ===== Oggetto complesso =====
struct MyObject {
  int id;
  std::string name;

  bool operator==(const MyObject& other) const {
    return id == other.id && name == other.name;
  }

  bool operator<(const MyObject& other) const {
    return id < other.id;
  }

  bool operator!=(const MyObject& other) const {
    return !(*this == other);
  }
};

// ===== Factory =====
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

// ===== Test suite =====
template <typename T>
void RunSetVecTests() {
  SetVec<T> set;

  // Insert
  ASSERT_TRUE(set.Insert(MakeValue<T>(1)));
  ASSERT_FALSE(set.Insert(MakeValue<T>(1))); // duplicate
  ASSERT_TRUE(set.Exists(MakeValue<T>(1)));
  ASSERT_EQ(set.Size(), 1);

  // Remove
  ASSERT_TRUE(set.Remove(MakeValue<T>(1)));
  ASSERT_FALSE(set.Remove(MakeValue<T>(1)));
  ASSERT_FALSE(set.Exists(MakeValue<T>(1)));

  // Min / Max
  set.Insert(MakeValue<T>(10));
  set.Insert(MakeValue<T>(30));
  set.Insert(MakeValue<T>(20));
  ASSERT_EQ(set.Min(), MakeValue<T>(10));
  ASSERT_EQ(set.Max(), MakeValue<T>(30));

  // MinNRemove / MaxNRemove
  T min = set.MinNRemove();
  ASSERT_EQ(min, MakeValue<T>(10));
  ASSERT_EQ(set.Min(), MakeValue<T>(20));

  T max = set.MaxNRemove();
  ASSERT_EQ(max, MakeValue<T>(30));
  ASSERT_EQ(set.Max(), MakeValue<T>(20));

  // Predecessor / Successor
  set.Clear();
  set.Insert(MakeValue<T>(10));
  set.Insert(MakeValue<T>(20));
  set.Insert(MakeValue<T>(30));
  ASSERT_EQ(set.Predecessor(MakeValue<T>(20)), MakeValue<T>(10));
  ASSERT_EQ(set.Successor(MakeValue<T>(20)), MakeValue<T>(30));

  // PredecessorNRemove / SuccessorNRemove
  ASSERT_EQ(set.PredecessorNRemove(MakeValue<T>(30)), MakeValue<T>(20));
  ASSERT_FALSE(set.Exists(MakeValue<T>(20)));

  ASSERT_EQ(set.SuccessorNRemove(MakeValue<T>(10)), MakeValue<T>(30));
  ASSERT_FALSE(set.Exists(MakeValue<T>(30)));

  // Out of bounds
  ASSERT_THROW(set.Min(), std::length_error);
  ASSERT_THROW(set.Max(), std::length_error);
  ASSERT_THROW(set.Predecessor(MakeValue<T>(10)), std::length_error);
  ASSERT_THROW(set.Successor(MakeValue<T>(10)), std::length_error);

  // Index operator
  set.Clear();
  set.Insert(MakeValue<T>(5));
  ASSERT_EQ(set[0], MakeValue<T>(5));
  ASSERT_THROW(set[1], std::out_of_range);

  // Copy constructor
  set.Insert(MakeValue<T>(6));
  SetVec<T> copy(set);
  ASSERT_EQ(copy.Size(), set.Size());
  ASSERT_EQ(copy[0], set[0]);
  ASSERT_TRUE(copy == set);

  // Move constructor
  SetVec<T> moved(std::move(set));
  ASSERT_EQ(moved.Size(), 2);

  // Copy assignment
  SetVec<T> assign;
  assign = copy;
  ASSERT_EQ(assign[0], copy[0]);

  // Move assignment
  SetVec<T> assign2;
  assign2 = std::move(copy);
  ASSERT_EQ(assign2[0], MakeValue<T>(5));

  // Comparison
  SetVec<T> a, b;
  a.Insert(MakeValue<T>(1));
  b.Insert(MakeValue<T>(1));
  ASSERT_TRUE(a == b);
  b.Insert(MakeValue<T>(2));
  ASSERT_TRUE(a != b);

  // Clear
  a.Clear();
  ASSERT_TRUE(a.Empty());

  std::cout << "All SetVec tests passed for type: " << typeid(T).name() << "\n";
}

// ===== Main =====
int main() {
  RunSetVecTests<int>();
  RunSetVecTests<std::string>();
  RunSetVecTests<MyObject>();
  return 0;
}
