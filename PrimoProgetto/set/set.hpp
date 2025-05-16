
#ifndef SET_HPP
#define SET_HPP

/* ************************************************************************** */

#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Set : public virtual OrderedDictionaryContainer<Data>,
             public virtual LinearContainer<Data>,
             public virtual ClearableContainer {
public:

  // Destructor
   ~Set() = default; // Destructor

  /* ************************************************************************ */

  // Copy assignment
  Set & operator=(const Set &)=delete; // Copy assignment of abstract types is not possible.
  // Move assignment
  Set & operator=(Set &&) noexcept = delete;// Move assignment of abstract types is not possible.

};

/* ************************************************************************** */

}

#endif
