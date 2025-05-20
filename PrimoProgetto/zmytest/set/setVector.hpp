 #ifndef TEST_SETVECTOR_HPP
#define TEST_SETVECTOR_HPP
#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <typeinfo>  // Necessario per typeid
#include <random>    // Per i test con numeri casuali
#include "../util/test_utils.hpp"
#include "../../vector/vector.hpp"
#include "../../set/vec/setvec.hpp"
#include <set>       // Per std::set nei test con valori unici


using namespace lasd;

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

  // Inserimento tramite std::move
  {
    T val = MakeValue<T>(99);
    ASSERT_TRUE(set.Insert(std::move(val)));
    ASSERT_TRUE(set.Exists(MakeValue<T>(99)));
  }

  // Move effettivo: l'oggetto sorgente deve risultare svuotato
  {
    SetVec<T> temp;
    temp.Insert(MakeValue<T>(1));
    temp.Insert(MakeValue<T>(2));
    SetVec<T> moved2 = std::move(temp);
    ASSERT_EQ(moved2.Size(), 2);
    ASSERT_TRUE(moved2.Exists(MakeValue<T>(1)));
    ASSERT_TRUE(moved2.Exists(MakeValue<T>(2)));
    ASSERT_TRUE(temp.Empty());
  }

  // Eccezioni realistiche di Predecessor/Successor
  {
    set.Clear();
    set.Insert(MakeValue<T>(10));
    set.Insert(MakeValue<T>(20));
    ASSERT_THROW(set.Predecessor(MakeValue<T>(10)), std::length_error);
    ASSERT_THROW(set.Successor(MakeValue<T>(20)), std::length_error);
  }

  // Verifica ordine logico interno (ordinamento)
  {
    set.Clear();
    set.Insert(MakeValue<T>(3));
    set.Insert(MakeValue<T>(1));
    set.Insert(MakeValue<T>(2));
    ASSERT_EQ(set[0], MakeValue<T>(1));
    ASSERT_EQ(set[1], MakeValue<T>(2));
    ASSERT_EQ(set[2], MakeValue<T>(3));
  }

  // Inserimento massivo di valori randomici
  {
    set.Clear();
    std::mt19937 gen(42); // seme fisso
    std::uniform_int_distribution<int> dist(0, 10000);
    std::set<T> uniqueValues;

    for (int i = 0; i < 500; ++i) {
      T val = MakeValue<T>(dist(gen));
      uniqueValues.insert(val);
      set.Insert(val); // Se duplicato, il set lo rifiuta (come atteso)
    }

    ASSERT_EQ(set.Size(), uniqueValues.size());
  }

  // Costruttore da TraversableContainer
  {
    Vector<T> vec;
    vec.Resize(3);
    vec[0] = MakeValue<T>(1);
    vec[1] = MakeValue<T>(2);
    vec[2] = MakeValue<T>(3);

    SetVec<T> fromVec(vec);
    ASSERT_EQ(fromVec.Size(), 3);
    ASSERT_TRUE(fromVec.Exists(MakeValue<T>(2)));
  }

  std::cout << "All SetVec tests passed for type: " << typeid(T).name() << "\n";
}

#endif // TEST_SETVECTOR_HPP