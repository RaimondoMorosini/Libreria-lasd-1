
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

#include <functional>
#include "traversable.hpp"
namespace lasd {

template <typename Data>
class MappableContainer : virtual public TraversableContainer<Data> {
public:

  virtual ~MappableContainer() = default; // Destructor
  
  MappableContainer & operator=(const MappableContainer &) = delete; // Copy assignment
  MappableContainer & operator=(MappableContainer &&) noexcept = delete; // Move assignment

  // Comparison operators
  bool operator==(const MappableContainer &) const noexcept = delete;
  bool operator!=(const MappableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  //function to map (required by class diagram)
  using MapFun = std::function<void(Data &)>; // Type alias for the mapping function
    virtual void Map(MapFun) = 0;

};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer : virtual public MappableContainer<Data>, virtual public PreOrderTraversableContainer<Data> {
public:

  virtual ~PreOrderMappableContainer() = default; // Destructor

  PreOrderMappableContainer & operator=(const PreOrderMappableContainer &) = delete;  // Copy assignment
  PreOrderMappableContainer & operator=(PreOrderMappableContainer &&) noexcept = delete;  // Move assignment

  // Comparison operators
  bool operator==(const PreOrderMappableContainer &) const noexcept = delete;
  bool operator!=(const PreOrderMappableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  //function to map (required by class diagram)
  using typename MappableContainer<Data>::MapFun; // Definisco un alias per il tipo MapFun della classe MappableContainer<Data> per utilizzarlo localmente.
  virtual void PreOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  inline void Map(MapFun) override;

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer : virtual public MappableContainer<Data>, virtual public PostOrderTraversableContainer<Data> {
public:

  virtual ~PostOrderMappableContainer() = default;  // Destructor

  PostOrderMappableContainer & operator=(const PostOrderMappableContainer &) = delete;  // Copy assignment
  PostOrderMappableContainer & operator=(PostOrderMappableContainer &&) noexcept = delete;  // Move assignment

  // Comparison operators
  bool operator==(const PostOrderMappableContainer &) const noexcept = delete;
  bool operator!=(const PostOrderMappableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // function to map (required by class diagram)
  using typename MappableContainer<Data>::MapFun; // Definisco un alias per il tipo MapFun della classe MappableContainer<Data> per utilizzarlo localmente.
  virtual void PostOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  inline void Map(MapFun) override;

};

}

#include "mappable.cpp"

#endif
