#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include "list.hpp"  // Assumendo che list.hpp includa anche list.cpp
using namespace lasd;

// ===== Helper macro per asserzioni semplici =====

#define ASSERT_EQ(x, y) assert((x) == (y))
#define ASSERT_TRUE(x)  assert(x)
#define ASSERT_FALSE(x) assert(!(x))
#define ASSERT_THROW(expr, exc_type)                        \
  try { expr; assert(false); } catch (const exc_type&) {}   \
  catch (...) { assert(false); }

// ===== Oggetto complesso di esempio =====

struct MyObject {
  int id;
  std::string name;

  bool operator==(const MyObject& other) const {
    return id == other.id && name == other.name;
  }

  bool operator!=(const MyObject& other) const {
    return !(*this == other);
  }
};

// ===== Factory per valori =====

template <typename T>
T MakeValue(int i); // dichiarazione

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

// ===== Funzione di test generica =====

template <typename T>
void RunListTests() {
  List<T> list;

  // InsertAtFront e InsertAtBack
  list.InsertAtFront(MakeValue<T>(10));
  list.InsertAtBack(MakeValue<T>(20));
  ASSERT_EQ(list.Front(), MakeValue<T>(10));
  ASSERT_EQ(list.Back(), MakeValue<T>(20));
  ASSERT_EQ(list[0], MakeValue<T>(10));
  ASSERT_EQ(list[1], MakeValue<T>(20));

  // RemoveFromFront
  list.Clear();
  list.InsertAtFront(MakeValue<T>(30));
  list.InsertAtFront(MakeValue<T>(40));
  ASSERT_EQ(list.Front(), MakeValue<T>(40));
  list.RemoveFromFront();
  ASSERT_EQ(list.Front(), MakeValue<T>(30));
  list.RemoveFromFront();
  ASSERT_THROW(list.RemoveFromFront(), std::length_error);

  // RemoveFromBack
  list.InsertAtBack(MakeValue<T>(50));
  list.InsertAtBack(MakeValue<T>(60));
  ASSERT_EQ(list.Back(), MakeValue<T>(60));
  list.RemoveFromBack();
  ASSERT_EQ(list.Back(), MakeValue<T>(50));
  list.RemoveFromBack();
  ASSERT_THROW(list.RemoveFromBack(), std::length_error);

  // FrontNRemove
  list.InsertAtBack(MakeValue<T>(70));
  T val1 = list.FrontNRemove();
  ASSERT_EQ(val1, MakeValue<T>(70));
  ASSERT_THROW(list.FrontNRemove(), std::length_error);

  // BackNRemove
  list.InsertAtFront(MakeValue<T>(80));
  T val2 = list.BackNRemove();
  ASSERT_EQ(val2, MakeValue<T>(80));
  ASSERT_THROW(list.BackNRemove(), std::length_error);

  // IndexAccessOutOfBounds
  ASSERT_THROW(list[0], std::out_of_range);
  list.InsertAtBack(MakeValue<T>(90));
  ASSERT_EQ(list[0], MakeValue<T>(90));
  ASSERT_THROW(list[1], std::out_of_range);

  // CopyConstructor
  list.Clear();
  list.InsertAtBack(MakeValue<T>(100));
  list.InsertAtBack(MakeValue<T>(200));
  List<T> copyList(list);
  ASSERT_EQ(copyList[0], list[0]);
  ASSERT_EQ(copyList[1], list[1]);

  // MoveConstructor
  list.Clear();
  list.InsertAtBack(MakeValue<T>(300));
  List<T> movedList(std::move(list));
  ASSERT_EQ(movedList[0], MakeValue<T>(300));
  ASSERT_EQ(movedList.Front(), MakeValue<T>(300));
  ASSERT_EQ(movedList.Back(), MakeValue<T>(300));
  ASSERT_EQ(movedList.Size(), 1);

  // ComparisonOperators
  List<T> list1;
  list1.InsertAtBack(MakeValue<T>(1));
  list1.InsertAtBack(MakeValue<T>(2));
  List<T> list2(list1);
  ASSERT_TRUE(list1 == list2);
  list2.InsertAtBack(MakeValue<T>(3));
  ASSERT_TRUE(list1 != list2);

  // Clear
  list2.Clear();
  ASSERT_TRUE(list2.Empty());
  ASSERT_EQ(list2.Size(), 0);

  // Traverse & Map (solo se T supporta operator int)
  list.Clear();
  for (int i = 0; i < 5; ++i)
    list.InsertAtBack(MakeValue<T>(i));

  int sum = 0;
  list.Traverse([&](const T& val) {
    sum += static_cast<int>(val.id); // compatibile solo con MyObject o int
  });

  // Map (esempio generico)
  list.Map([](T& val) {
    val = MakeValue<T>(999);
  });

  std::cout << "All tests passed for type: " << typeid(T).name() << "\n";
}

// ===== Main =====

int main() {
  RunListTests<int>();
  RunListTests<std::string>();
  RunListTests<MyObject>();
  return 0;
}
