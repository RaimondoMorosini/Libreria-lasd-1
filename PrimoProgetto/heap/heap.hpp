
#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Heap : virtual public SortableLinearContainer<Data>,  virtual public ClearableContainer {
  // Must extend SortableLinearContainer<Data>,
  //Must extend              ClearableContainer

private:

protected:

public:

  virtual ~Heap()= default; // Destructor

  /* ************************************************************************ */

  Heap & operator=(const Heap &) = delete; // Copy assignment of abstract types is not possible.
  Heap & operator=(Heap &&) noexcept = delete; // Move assignment of abstract types is not possible.
  /* ************************************************************************ */

  // Specific member functions

  bool IsHeap() const noexcept =delete;

  void Heapify() = delete;

};

/* ************************************************************************** */

}

#endif
