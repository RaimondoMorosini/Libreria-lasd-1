#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : public Set<Data>, protected Vector<Data> {

private:

  using Vector<Data>::Elements;

  ulong head = 0;     // Indice dell’inizio del buffer circolare
  ulong tail = 0;     // Indice della fine del buffer (prossima posizione libera)
  ulong size = 0;     // Numero di elementi effettivamente contenuti
  ulong& capacity = this->Vector<Data>::size; // Capacità del buffer circolare

protected:

public:

  // Default constructor
  SetVec();

  /* ************************************************************************ */

  // Specific constructors
  SetVec(const TraversableContainer<Data>&);
  SetVec(MappableContainer<Data>&&);

  /* ************************************************************************ */

  // Copy constructor
  SetVec(const SetVec&);

  // Move constructor
  SetVec(SetVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~SetVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  SetVec& operator=(const SetVec&);

  // Move assignment
  SetVec& operator=(SetVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetVec&) const noexcept;
  inline bool operator!=(const SetVec&) const noexcept;

  /* ************************************************************************ */

  // OrderedDictionaryContainer member functions
  const Data& Min() const override;
  Data MinNRemove() override;
  void RemoveMin() override;

  const Data& Max() const override;
  Data MaxNRemove() override;
  void RemoveMax() override;

  const Data& Predecessor(const Data&) const override;
  Data PredecessorNRemove(const Data&) override;
  void RemovePredecessor(const Data&) override;

  const Data& Successor(const Data&) const override;
  Data SuccessorNRemove(const Data&) override;
  void RemoveSuccessor(const Data&) override;

  /* ************************************************************************ */

  // DictionaryContainer member functions
  bool Insert(const Data&) override;
  bool Insert(Data&&) override;
  bool Remove(const Data&) override;

  /* ************************************************************************ */

  // LinearContainer member function
  const Data& operator[](ulong) const override;
  Data& operator[](ulong) override;

  /* ************************************************************************ */

  // TestableContainer member function
  bool Exists(const Data&) const noexcept override;

  /* ************************************************************************ */

  // ClearableContainer member function
  void Clear() override;

protected:

  // Auxiliary functions

  void Resize(ulong); // Aumenta la capacità del vettore

  ulong LowerBoundIndex(const Data&) const; // Ricerca binaria ordinata

  void ShiftLeft(ulong, ulong); // Shift logico a sinistra nel buffer circolare
  void ShiftRight(ulong, ulong); // Shift logico a destra nel buffer circolare

  ulong RealIndex(ulong) const; // Converte un indice logico in fisico
};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif
