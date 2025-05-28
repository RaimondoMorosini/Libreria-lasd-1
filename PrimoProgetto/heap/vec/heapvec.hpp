#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : virtual public Heap<Data>,virtual protected Vector<Data> {

private:

  // Auxiliary function to maintain heap property
  void HeapifyDown(ulong); // From index downward
  void HeapifyUp(ulong);   // From index upward

protected:

  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  // Default constructor
  HeapVec() = default;

  // Specific constructors
  HeapVec(const TraversableContainer<Data>&);
  HeapVec(MappableContainer<Data>&&);

  // Copy constructor
  HeapVec(const HeapVec&);

  // Move constructor
  HeapVec(HeapVec&&) noexcept;

  // Destructor
  ~HeapVec() = default;

  // Copy assignment
  HeapVec& operator=(const HeapVec&);

  // Move assignment
  HeapVec& operator=(HeapVec&&) noexcept;

  // Comparison operators
  bool operator==(const HeapVec&) const noexcept;
  bool operator!=(const HeapVec&) const noexcept;

  // Heap functions
  bool IsHeap() const noexcept override;
  void Heapify() override;

  // SortableLinearContainer function
void Sort() noexcept override;
};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
