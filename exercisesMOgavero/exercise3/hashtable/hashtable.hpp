
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:

  ulong operator()(const Data & dat) const noexcept = 0;

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public ResizableContainer,
  virtual public DictionaryContainer<Data> {

private:

protected:

  using DictionaryContainer<Data>::size;

  ulong acoeff = 1;
  ulong bcoeff = 0;
  static const ulong prime = 1000000016531;

  std::default_random_engine gen = std::default_random_engine(std::random_device {}());
  std::uniform_int_distribution<ulong> dista = std::uniform_int_distribution<ulong>(1, prime - 1);
  std::uniform_int_distribution<ulong> distb = std::uniform_int_distribution<ulong>(0, prime - 1);

  static const Hashable<Data> enchash;

  ulong tablesize = 128;

  /* ************************************************************************ */

  // Default constructor
  HashTable() {
    acoeff = dista(gen);
    bcoeff = distb(gen);
  }

  /* ************************************************************************ */

  // Copy constructor
  HashTable(const HashTable & ht) {
    size = ht.size;
    acoeff = ht.acoeff;
    bcoeff = ht.bcoeff;
    tablesize = ht.tablesize;
  }

  // Move constructor
  HashTable(HashTable && ht) noexcept {
    std::swap(size, ht.size);
    std::swap(acoeff, ht.acoeff);
    std::swap(bcoeff, ht.bcoeff);
    std::swap(tablesize, ht.tablesize);
  }

  /* ************************************************************************ */

  // Copy assignment
  HashTable & operator=(const HashTable & ht) {
    size = ht.size;
    acoeff = ht.acoeff;
    bcoeff = ht.bcoeff;
    tablesize = ht.tablesize;
    return *this;
  }

  // Move assignment
  HashTable & operator=(HashTable && ht) noexcept {
    std::swap(size, ht.size);
    std::swap(acoeff, ht.acoeff);
    std::swap(bcoeff, ht.bcoeff);
    std::swap(tablesize, ht.tablesize);
    return *this;
  }

public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable &) const noexcept = delete;
  bool operator!=(const HashTable &) const noexcept = delete;

protected:

  virtual ulong HashKey(const Data & dat) const noexcept {
    return HashKey(enchash(dat));
  }

  virtual ulong HashKey(ulong key) const noexcept {
    return (((acoeff * key + bcoeff) % prime) % tablesize);
  }

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
