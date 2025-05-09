
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : virtual public HashTable<Data> {

private:

protected:

  using HashTable<Data>::size;
  using HashTable<Data>::tablesize;

  using HashTable<Data>::HashKey;
  using HashTable<Data>::Insert;
  using HashTable<Data>::InsertAll;

  BST<Data> * Table = nullptr;

public:

  // Default constructor
  HashTableClsAdr();

  /* ************************************************************************ */

  // Specific constructors

  HashTableClsAdr(ulong);

  HashTableClsAdr(const TraversableContainer<Data> &);
  HashTableClsAdr(ulong, const TraversableContainer<Data> &);

  HashTableClsAdr(MappableContainer<Data> &&);
  HashTableClsAdr(ulong, MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr &);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableClsAdr();

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr & operator=(const HashTableClsAdr &);

  // Move assignment
  HashTableClsAdr & operator=(HashTableClsAdr &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr &) const noexcept;
  bool operator!=(const HashTableClsAdr &) const noexcept;

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

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
