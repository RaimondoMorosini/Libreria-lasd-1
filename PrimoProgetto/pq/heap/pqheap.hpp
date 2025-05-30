
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : virtual public PQ<Data>,
                virtual protected HeapVec<Data> { 
protected:

  using Container::size;
  using Vector<Data>::Elements;
  using Vector<Data>::Resize;
  using HeapVec<Data>::HeapifyDown;
  using HeapVec<Data>::HeapifyUp;

public:

  PQHeap() = default; // Default constructor
  

  /* ************************************************************************ */

  // Specific constructors
  
  // PQHeap(argument) specifiers; // A priority queue obtained from a TraversableContainer
  PQHeap(const TraversableContainer<Data>& con) : HeapVec<Data>(con) {}  
  // PQHeap(argument) specifiers; // A priority queue obtained from a MappableContainer
  PQHeap(MappableContainer<Data>&& con) : HeapVec<Data>(std::move(con)) {}
  /* ************************************************************************ */

  // Copy constructor
  PQHeap(const PQHeap<Data>& other) : HeapVec<Data>(other) {} 
  
  // Move constructor
  PQHeap(PQHeap<Data>&& other) noexcept : HeapVec<Data>(std::move(other)) {} 
  /* ************************************************************************ */

  ~PQHeap()= default; // Destructor

  /* ************************************************************************ */

  // Copy assignment
PQHeap<Data>& operator=(const PQHeap<Data>& );
  // Move assignment
PQHeap<Data>& operator=(PQHeap<Data>&& ) noexcept ;
  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  const Data& Tip() const override; // Override PQ member (must throw std::length_error when empty)
  void RemoveTip() override; // Override PQ member (must throw std::length_error when empty)                
  Data TipNRemove() override; // Override PQ member (must throw std::length_error when empty)
  
 void Insert(const Data& dat) override; // Override PQ member (Copy of the value) 
  void Insert(Data&& dat) override; // Override PQ member (Move of the value)
  
  void Change(const ulong index, const Data& dat) override; // Override PQ member (Copy of the value)
  void Change(const ulong index, Data&& dat) override; // Override PQ member (Move of the value)

protected:


};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
