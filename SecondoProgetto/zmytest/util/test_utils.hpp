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


//funzioni che creano un oggetto di tipo T da un container 
template <template <typename> class C, typename T, typename Traversable>
C<T> MakeFromContainer(const Traversable& source) {
    return C<T>(source); // Usa il costruttore const Traversable&
}

template <template <typename> class C, typename T, typename Mappable>
C<T> MakeFromContainer(Mappable&& source) {
    return C<T>(std::move(source)); // Usa il costruttore Mappable&&
}

// ===================
//funzione che crea un oggetto di tipo T da un container usando il costruttore di copia ed poi applica la funzione testFn
template <template <typename> class C, typename T, typename Traversable, typename TestFunc>
void TestConstructionCopy(const Traversable& source, TestFunc testFn) {
    C<T> container(source); // Costruttore per copia
    testFn(container);      // Applica i test
}

//funzione che crea un oggetto di tipo T da un container usando il costruttore di move ed poi applica la funzione testFn
template <template <typename> class C, typename T, typename Mappable, typename TestFunc>
void TestConstructionMove(Mappable&& source, TestFunc testFn) {
    C<T> container(std::move(source)); // Costruttore per move
    testFn(container);                 // Applica i test
}




#endif // TEST_UTILS_HPP
