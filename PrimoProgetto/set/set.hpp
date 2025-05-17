
#ifndef SET_HPP
#define SET_HPP

/* ************************************************************************** */

#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"
#include "../container/linear.hpp"

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



  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual bool Insert(const Data &) = 0;   // Inserimento per copia
  virtual bool Insert(Data &&) = 0;        // Inserimento per move
  virtual bool Remove(const Data &) = 0;   // Rimozione dell'elemento

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  virtual const Data & Min() const = 0;                    // Restituisce il minimo (std::length_error se vuoto)
  virtual Data MinNRemove() = 0;                           // Restituisce e rimuove il minimo (std::length_error se vuoto)
  virtual void RemoveMin() = 0;                            // Rimuove il minimo (std::length_error se vuoto)

  virtual const Data & Max() const = 0;                    // Restituisce il massimo (std::length_error se vuoto)
  virtual Data MaxNRemove() = 0;                           // Restituisce e rimuove il massimo (std::length_error se vuoto)
  virtual void RemoveMax() = 0;                            // Rimuove il massimo (std::length_error se vuoto)

  virtual const Data & Predecessor(const Data &) const = 0; // Restituisce il predecessore (std::length_error se non trovato)
  virtual Data PredecessorNRemove(const Data &) = 0;        // Restituisce e rimuove il predecessore (std::length_error se non trovato)
  virtual void RemovePredecessor(const Data &) = 0;         // Rimuove il predecessore (std::length_error se non trovato)

  virtual const Data & Successor(const Data &) const = 0;   // Restituisce il successore (std::length_error se non trovato)
  virtual Data SuccessorNRemove(const Data &) = 0;          // Restituisce e rimuove il successore (std::length_error se non trovato)
  virtual void RemoveSuccessor(const Data &) = 0;           // Rimuove il successore (std::length_error se non trovato)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  virtual const Data & operator[](ulong) const = 0; // Accesso elemento (std::out_of_range se fuori indice)

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)

  virtual bool Exists(const Data &) const noexcept = 0; // Verifica se un dato esiste nella struttura

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() = 0; // Rimozione di tutti gli elementi

  };
}

#endif
