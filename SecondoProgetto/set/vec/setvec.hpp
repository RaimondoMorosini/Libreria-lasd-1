#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */
/*
  setvec.hpp - Definizione della classe SetVec

  Questo header definisce la classe template `SetVec`, un contenitore che implementa
  un set (insieme ordinato crescente, senza duplicati) utilizzando un `Vector` come struttura
  di supporto.

  Per migliorare l'efficienza del ridimensionamento automatico dello spazio allocato,
  gli elementi sono memorizzati in un array circolare, mantenuti in ordine.

  La classe fornisce metodi per inserire, rimuovere e cercare elementi, oltre a
  operazioni su minimi, massimi, predecessori e successori. Supporta anche
  traversamento e mappatura attraverso le interfacce ereditate.

  Autore: Raimondo Morosini
*/

/* ************************************************************************** */
#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : public virtual Set<Data>,
               public virtual ResizableContainer {
protected:
  using Container::size;

  Vector<Data> vec;  // vettore base
  ulong head = 0;    // inizio logico
  ulong tail = 0;    // fine logico 

  // size --> numero di elementi attuali (già ereditato da Container)
  // vec.Size() --> capacità totale del buffer

public:

  // Default constructor
  SetVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  SetVec(const TraversableContainer<Data> &); // A set obtained from a TraversableContainer
  // SetVec(argument) specifiers; // A set obtained from a MappableContainer
  SetVec(MappableContainer<Data> &&);

  /* ************************************************************************ */

  SetVec(const SetVec &); // Copy constructor;

  SetVec(SetVec &&) noexcept; // Move constructor;

  ~SetVec() = default; // Destructor

  /* ************************************************************************ */

  // Copy assignment
  SetVec & operator=(const SetVec &);

  // Move assignment
  SetVec & operator=(SetVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const SetVec &) const noexcept; // type operator==(argument) specifiers;
  inline bool operator!=(const SetVec &) const noexcept; // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  const Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](ulong); // Non-const version for internal use

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  // Specific member function (inherited from ResizableContainer)
    void Resize(ulong) override ; // Resize the vector to a new capacity


protected:

  // Auxiliary functions

  //Binary search helper
  ulong LowerBoundIndex(const Data& val) const; // Find the index of a value using binary search


};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif