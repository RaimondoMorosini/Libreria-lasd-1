
#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Heap : virtual public SortableLinearContainer<Data>,  virtual public ClearableContainer {
public:

  virtual ~Heap()= default; // Destructor

  Heap & operator=(const Heap &) = delete; // Copy assignment of abstract types is not possible.
  Heap & operator=(Heap &&) noexcept = delete; // Move assignment of abstract types is not possible.
  /* ************************************************************************ */

  // functions required by the class diagram

  virtual bool IsHeap() const noexcept = 0; // Check if the container is a heap

  virtual void Heapify() = 0; // Transform the container into a heap
};

/* ************************************************************************** */

}

#endif
