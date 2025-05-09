
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>,
  virtual protected List<Data> {

private:

protected:

public:

  // Default constructor
  inline StackLst() = default;

  /* ************************************************************************ */

  // Specific constructors
  StackLst(const TraversableContainer<Data> & con) : List<Data>(con) {};
  StackLst(MappableContainer<Data> && con) : List<Data>(std::move(con)) {};

  /* ************************************************************************ */

  // Copy constructor
  inline StackLst(const StackLst & stk) : List<Data>(stk) {};

  // Move constructor
  inline StackLst(StackLst && stk) noexcept : List<Data>(std::move(stk)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline StackLst & operator=(const StackLst &);

  // Move assignment
  inline StackLst & operator=(StackLst &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const StackLst &) const noexcept;
  inline bool operator!=(const StackLst &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  inline const Data & Top() const override;
  inline Data & Top() override;
  inline void Pop() override;
  inline Data TopNPop() override;
  inline void Push(const Data &) override;
  inline void Push(Data &&) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
