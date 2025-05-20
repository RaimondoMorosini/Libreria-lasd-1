#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <typeinfo>
#include <random>
#include <set>
#include "../../vector/vector.hpp"
#include "setlst.hpp"

using namespace lasd;

#define ASSERT_EQ(x, y) assert((x) == (y))
#define ASSERT_TRUE(x)  assert(x)
#define ASSERT_FALSE(x) assert(!(x))
#define ASSERT_THROW(expr, exc_type)                        \
  try { expr; assert(false); } catch (const exc_type&) {}   \
  catch (...) { assert(false); }

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
};


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

template <typename T>
void RunSetLstTests() {
  SetLst<T> set;

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

  // Eccezioni: Min/Max/Predecessor/Successor su set vuoto
  set.Clear();
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
  SetLst<T> copy(set);
  ASSERT_EQ(copy.Size(), set.Size());
  ASSERT_EQ(copy[0], set[0]);
  ASSERT_TRUE(copy == set);

  // Move constructor
  SetLst<T> moved(std::move(set));
  ASSERT_EQ(moved.Size(), 2);

  // Copy assignment
  SetLst<T> assign;
  assign = copy;
  ASSERT_EQ(assign[0], copy[0]);

  // Move assignment
  SetLst<T> assign2;
  assign2 = std::move(copy);
  ASSERT_EQ(assign2[0], MakeValue<T>(5));

  // Comparison
  SetLst<T> a, b;
  a.Insert(MakeValue<T>(1));
  b.Insert(MakeValue<T>(1));
  ASSERT_TRUE(a == b);
  b.Insert(MakeValue<T>(2));
  ASSERT_TRUE(a != b);

  // Clear
  a.Clear();
  ASSERT_TRUE(a.Empty());

  // Inserimento tramite std::move
  {
    T val = MakeValue<T>(99);
    ASSERT_TRUE(set.Insert(std::move(val)));
    ASSERT_TRUE(set.Exists(MakeValue<T>(99)));
  }

  // Move effettivo: il set sorgente deve risultare svuotato
  {
    SetLst<T> temp;
    temp.Insert(MakeValue<T>(1));
    temp.Insert(MakeValue<T>(2));
    SetLst<T> moved2 = std::move(temp);
    ASSERT_EQ(moved2.Size(), 2);
    ASSERT_TRUE(moved2.Exists(MakeValue<T>(1)));
    ASSERT_TRUE(moved2.Exists(MakeValue<T>(2)));
    ASSERT_TRUE(temp.Empty());
  }

  // Predecessor / Successor: eccezioni realistiche
  {
    set.Clear();
    set.Insert(MakeValue<T>(10));
    set.Insert(MakeValue<T>(20));
    ASSERT_THROW(set.Predecessor(MakeValue<T>(10)), std::length_error);
    ASSERT_THROW(set.Successor(MakeValue<T>(20)), std::length_error);
  }

  // Verifica ordinamento
  {
    set.Clear();
    set.Insert(MakeValue<T>(3));
    set.Insert(MakeValue<T>(1));
    set.Insert(MakeValue<T>(2));
    ASSERT_EQ(set[0], MakeValue<T>(1));
    ASSERT_EQ(set[1], MakeValue<T>(2));
    ASSERT_EQ(set[2], MakeValue<T>(3));
  }

  // Inserimento massivo con valori unici
  {
    set.Clear();
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(0, 10000);
    std::set<T> uniqueValues;

    for (int i = 0; i < 500; ++i) {
      T val = MakeValue<T>(dist(gen));
      uniqueValues.insert(val);
      set.Insert(val);
    }

    ASSERT_EQ(set.Size(), uniqueValues.size());
  }

  // Costruttore da container
  {
    Vector<T> vec;
    vec.Resize(3);
    vec[0] = MakeValue<T>(1);
    vec[1] = MakeValue<T>(2);
    vec[2] = MakeValue<T>(3);

    SetLst<T> fromVec(vec);
    ASSERT_EQ(fromVec.Size(), 3);
    ASSERT_TRUE(fromVec.Exists(MakeValue<T>(2)));
  }

  std::cout << "All SetLst tests passed for type: " << typeid(T).name() << "\n";
}

int main() {
  RunSetLstTests<int>();
  RunSetLstTests<std::string>();
  RunSetLstTests<MyObject>();
  return 0;
}
