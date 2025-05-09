
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>,
  virtual protected Vector<Data> {

private:

protected:

  ulong index = 0;

  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  // Default constructor
  StackVec() : Vector<Data>(1) {};

  /* ************************************************************************ */

  // Specific constructors
  StackVec(const TraversableContainer<Data> & con) : Vector<Data>(con), index(size) {};
  StackVec(MappableContainer<Data> && con) : Vector<Data>(std::move(con)), index(size) {};

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec & stk) : Vector<Data>(stk), index(stk.index) {};

  // Move constructor
  StackVec(StackVec &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec & operator=(const StackVec &);

  // Move assignment
  StackVec & operator=(StackVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec &) const noexcept;
  inline bool operator!=(const StackVec &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data & Top() const override;
  Data & Top() override;
  void Pop() override;
  Data TopNPop() override;
  void Push(const Data &) override;
  void Push(Data &&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override;

  inline ulong Size() const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

protected:

  // Auxiliary member functions

  void Expand();
  void Reduce();

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
