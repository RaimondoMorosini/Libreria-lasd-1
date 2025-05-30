
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class PQHeap : virtual public PQ<Data>,
                 virtual protected HeapVec<Data>
  {
  protected:
    using Container::size;
    using Vector<Data>::Elements;
    using Vector<Data>::Resize;

    ulong heapSize = 0; // Size of the heap (number of elements in the heap)

  public:
    PQHeap() = default; // Default constructor

    /* ************************************************************************ */

    // Specific constructors

    // PQHeap(argument) specifiers; // A priority queue obtained from a TraversableContainer
    PQHeap(const TraversableContainer<Data> &con) : HeapVec<Data>(con) {
      heapSize = con.Size(); // Initialize heap size from the container size
    }
    // PQHeap(argument) specifiers; // A priority queue obtained from a MappableContainer
    PQHeap(MappableContainer<Data> &&con) : HeapVec<Data>(std::move(con)) {
      heapSize = con.Size(); // Initialize heap size from the container size
    }
    /* ************************************************************************ */

    // Copy constructor
    PQHeap(const PQHeap<Data> &other) : HeapVec<Data>(other) {
      heapSize = other.heapSize; // Copy the heap size
     }

    // Move constructor
    PQHeap(PQHeap<Data> &&other) noexcept : HeapVec<Data>(std::move(other)) {
      std::swap(heapSize, other.heapSize); // Move the heap size
    }
    /* ************************************************************************ */

    ~PQHeap() = default; // Destructor

    /* ************************************************************************ */

    // Copy assignment
    PQHeap<Data> &operator=(const PQHeap<Data> &);
    // Move assignment
    PQHeap<Data> &operator=(PQHeap<Data> &&) noexcept;
    /* ************************************************************************ */

    // Specific member functions (inherited from PQ)

    const Data &Tip() const override; // Override PQ member (must throw std::length_error when empty)
    void RemoveTip() override;        // Override PQ member (must throw std::length_error when empty)
    Data TipNRemove() override;       // Override PQ member (must throw std::length_error when empty)

    void Insert(const Data &dat) override; // Override PQ member (Copy of the value)
    void Insert(Data &&dat) override;      // Override PQ member (Move of the value)

    void Change(const ulong index, const Data &dat) override; // Override PQ member (Copy of the value)
    void Change(const ulong index, Data &&dat) override;      // Override PQ member (Move of the value)

    //specific member functions (inherited from Container)
    ulong Size() const noexcept override {
      return heapSize; // Return the current size of the heap
    }
  protected:
  //ausiliary function to get the current capacity of the heap
  ulong GetCapacity() const;
  //heapify function to maintain the heap property
  


  };

  /* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
