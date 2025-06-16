
#ifndef PQ_HPP
#define PQ_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQ : virtual public LinearContainer<Data>,
           virtual public ClearableContainer  {

public:

  virtual ~PQ() = default; // Destructor
  PQ & operator=(const PQ &) = delete; // Copy assignment of abstract types is not possible.
  PQ & operator=(PQ &&) noexcept = delete; // Move assignment of abstract types is not possible.
  /* ************************************************************************ */

  // Specific required by the class diagram

  virtual const Data& Tip() const = 0; // Get the tip of the priority queue (must throw std::length_error when empty)
  virtual void RemoveTip() = 0; // Remove the tip of the priority queue (must throw std::length_error when empty)
  virtual Data TipNRemove() = 0; // Get the tip of the priority queue and remove it (must throw std::length_error when empty)

  virtual void Insert(const Data&) = 0; // Insert a value into the priority queue (copy of the value)
  virtual void Insert(Data&&) = 0; // Insert a value into the priority queue (move of the value)


  virtual void Change(const ulong, const Data&) = 0; // Change the tip of the priority queue (copy of the value)
  virtual void Change(const ulong, Data&&) = 0; // Change the tip of the priority queue (move of the value)

};

/* ************************************************************************** */

}

#endif
