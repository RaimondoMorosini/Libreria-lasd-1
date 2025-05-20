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
  using Vector<Data>::size; // ATTENZIONE: questo rappresenta la CAPACITÀ

  ulong head = 0;
  ulong numeroDiElementi = 0; // Numero di elementi effettivamente presenti

protected:

  ulong RealIndex(ulong) const; // Converte un indice logico in fisico

public:

  // Default constructor
  SetVec();

  // Specific constructors
  SetVec(const TraversableContainer<Data>&);
  SetVec(MappableContainer<Data>&&);

  // Copy constructor
  SetVec(const SetVec&);

  // Move constructor
  SetVec(SetVec&&) noexcept;

  // Destructor
  ~SetVec() = default;

  // Copy assignment
  SetVec& operator=(const SetVec&);

  // Move assignment
  SetVec& operator=(SetVec&&) noexcept;

  // Comparison operators
  bool operator==(const SetVec&) const noexcept;
  inline bool operator!=(const SetVec&) const noexcept;

  // DictionaryContainer
  bool Insert(const Data&) override;
  bool Insert(Data&&) override;
  bool Remove(const Data&) override;

  // OrderedDictionaryContainer 
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


  // LinearContainer
  const Data& operator[](ulong) const override;
  Data& operator[](ulong) override;

  // TestableContainer
  bool Exists(const Data&) const noexcept override;

  // ClearableContainer
  void Clear() override;

  // Container
  ulong Size() const noexcept override { return numeroDiElementi; }

protected:

  void Resize(ulong);
  ulong LowerBoundIndex(const Data&) const;

  void ShiftLeft(ulong, ulong);
  void ShiftRight(ulong, ulong);
};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif