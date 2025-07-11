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


protected:

  using Container::size;
  using Vector<Data>::Elements;
    // Auxiliary function to maintain heap property
  void HeapifyDown(ulong); // From index downward
  void HeapifyUp(ulong);   // From index upward

public:

  //espongo Front e Back
 using LinearContainer<Data>::Front; // const Front()
using LinearContainer<Data>::Back;  // const Back()

using MutableLinearContainer<Data>::Front; // non-const Front()
using MutableLinearContainer<Data>::Back;  // non-const Back()

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

  // ClearableContainer function
  void Clear() noexcept override { // Override ClearableContainer member
    Vector<Data>::Clear(); // Call the Clear method of the base class
  } // No need to throw exceptions, as Clear is not expected to fail
};



/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
