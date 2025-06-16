#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

#include <functional>
#include "testable.hpp"


namespace lasd{

template <typename Data>
class TraversableContainer : virtual public TestableContainer<Data> {

public:

  virtual ~TraversableContainer() = default;  // Destructor

  TraversableContainer & operator=(const TraversableContainer &) = delete;  // Copy assignment
  TraversableContainer & operator=(TraversableContainer &&) noexcept = delete; // Move assignment

  // Comparison operators
  bool operator==(const TraversableContainer &) const noexcept = delete;
  bool operator!=(const TraversableContainer &) const noexcept = delete;

/* ************************************************************************ */

  //function to traverse the container (required by class diagram)
  using TraverseFun = std::function<void(const Data &)>; //alias for the function type

  virtual void Traverse(TraverseFun) const = 0;

  //function to fold the container (required by class diagram)
  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>; //alias for the function type

  template <typename Accumulator>
  Accumulator Fold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)
  inline bool Exists(const Data &) const noexcept override;

};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : virtual public TraversableContainer<Data> {
public:

  virtual ~PreOrderTraversableContainer() = default;   // Destructor

  PreOrderTraversableContainer & operator=(const PreOrderTraversableContainer &) = delete;   // Copy assignment
  PreOrderTraversableContainer & operator=(PreOrderTraversableContainer &&) noexcept = delete;   // Move assignment


  // Comparison operators
  bool operator==(const PreOrderTraversableContainer &) const noexcept = delete;
  bool operator!=(const PreOrderTraversableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // function to traverse the container (required by class diagram)
  using typename TraversableContainer<Data>::TraverseFun; //alias for the function type

  virtual void PreOrderTraverse(TraverseFun) const = 0;

  // function to fold the container (required by class diagram)
  template <typename Accumulator> //alias for the function type
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  inline void Traverse(TraverseFun) const override;

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer : virtual public TraversableContainer<Data> {
public:

  virtual ~PostOrderTraversableContainer() = default; // Destructor

  
  PostOrderTraversableContainer & operator=(const PostOrderTraversableContainer &) = delete; // Copy assignment

  PostOrderTraversableContainer & operator=(PostOrderTraversableContainer &&) noexcept = delete; // Move assignment

  // Comparison operators
  bool operator==(const PostOrderTraversableContainer &) const noexcept = delete;
  bool operator!=(const PostOrderTraversableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // function to traverse the container (required by class diagram
  using typename TraversableContainer<Data>::TraverseFun; //alias for the function type
  virtual void PostOrderTraverse(TraverseFun) const = 0;

  // function to fold the container (required by class diagram)
  template <typename Accumulator> 
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>; //alias for the function type

  template <typename Accumulator>
  Accumulator PostOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  inline void Traverse(TraverseFun) const override;

};


}

#include "traversable.cpp"

#endif
