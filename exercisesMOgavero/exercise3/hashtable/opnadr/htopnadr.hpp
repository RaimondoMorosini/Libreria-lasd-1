
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> {

private:

protected:

  ulong ccoeff = 1;
  ulong dcoeff = 0;
  using HashTable<Data>::prime;

  using HashTable<Data>::gen;
  using HashTable<Data>::dista;
  using HashTable<Data>::distb;

  using HashTable<Data>::enchash;

  using HashTable<Data>::size;
  using HashTable<Data>::tablesize;

  using HashTable<Data>::HashKey;
  using HashTable<Data>::Insert;
  using HashTable<Data>::InsertAll;

  Vector<Data> table = Vector<Data>(tablesize);
  Vector<char> flagtable = Vector<char>(tablesize);

public:

  // Default constructor
  HashTableOpnAdr() {
    ccoeff = 2 * dista(gen) + 1;
    dcoeff = 2 * distb(gen);
  }

  /* ************************************************************************ */

  // Specific constructors

  HashTableOpnAdr(ulong);

  HashTableOpnAdr(const TraversableContainer<Data> &);
  HashTableOpnAdr(ulong, const TraversableContainer<Data> &);

  HashTableOpnAdr(MappableContainer<Data> &&);
  HashTableOpnAdr(ulong, MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr &);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr & operator=(const HashTableOpnAdr &);

  // Move assignment
  HashTableOpnAdr & operator=(HashTableOpnAdr &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr &) const noexcept;
  bool operator!=(const HashTableOpnAdr &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override;
  bool Insert(Data &&) override;
  bool Remove(const Data &) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data &) const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(ulong) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() override;

protected:

  virtual ulong HashKey(const Data & dat, ulong idx) const noexcept;

  virtual ulong HashIdx(ulong key) const noexcept;

  virtual ulong Find(const Data & dat, ulong idx) const noexcept;

  virtual ulong FindEmpty(const Data & dat, ulong idx) const noexcept;

  virtual bool Remove(const Data &, ulong idx);

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
