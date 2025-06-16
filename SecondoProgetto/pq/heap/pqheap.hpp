
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"
//include iostream for debugging purposes
#include <iostream>

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
    using HeapVec<Data>::HeapifyDown;
    using HeapVec<Data>::HeapifyUp;


  public:
    PQHeap() = default; // Default constructor

    /* ************************************************************************ */

    // Specific constructors
PQHeap(const TraversableContainer<Data>&); // da TraversableContainer
PQHeap(MappableContainer<Data>&&);         // da MappableContainer (move)


//copy constructor
PQHeap(const PQHeap<Data>&);

//move constructor
PQHeap(PQHeap<Data>&&) noexcept;

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

    /* ************************************************************************ */
    // Specific member functions (inherited from CleanContainer)
    void Clear() noexcept override { // Override CleanableContainer member
      HeapVec<Data>::Clear(); // Call the Clear method of the base class
    } // No need to throw exceptions, as Clear is not expected to fail

      //espongo Front e Back
 using LinearContainer<Data>::Front; // const Front()
using LinearContainer<Data>::Back;  // const Back()
   

  protected:


  };

  /* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
