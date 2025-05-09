
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public ClearableContainer,
  virtual public DictionaryContainer<Data>,
  virtual public BinaryTree<Data>,
  virtual protected BinaryTreeLnk<Data> {

private:

protected:

  using typename BinaryTreeLnk<Data>::NodeLnk;

  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const TraversableContainer<Data> &);
  BST(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST & bst) : BinaryTreeLnk<Data>(bst) {};

  // Move constructor
  BST(BST && bst) noexcept : BinaryTreeLnk<Data>(std::move(bst)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST & operator=(const BST &);

  // Move assignment
  BST & operator=(BST &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  using BinaryTree<Data>::operator==;
  inline bool operator==(const BST &) const noexcept;
  using BinaryTree<Data>::operator!=;
  inline bool operator!=(const BST &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data & Min() const;
  virtual Data MinNRemove();
  virtual void RemoveMin();

  virtual const Data & Max() const;
  virtual Data MaxNRemove();
  virtual void RemoveMax();

  virtual const Data & Predecessor(const Data &) const;
  virtual Data PredecessorNRemove(const Data &);
  virtual void RemovePredecessor(const Data &);

  virtual const Data & Successor(const Data &) const;
  virtual Data SuccessorNRemove(const Data &);
  virtual void RemoveSuccessor(const Data &);

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using BinaryTreeLnk<Data>::Clear;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data &) const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override;
  bool Insert(Data &&) override;
  bool Remove(const Data &) override;

  // Specific member function (inherited from BinaryTree)

  using BinaryTreeLnk<Data>::Root;

protected:

  // Auxiliary member functions

  virtual Data DataNDelete(NodeLnk *);

  virtual NodeLnk * Detach(NodeLnk *&) noexcept;

  virtual NodeLnk * DetachMin(NodeLnk *&) noexcept;
  virtual NodeLnk * DetachMax(NodeLnk *&) noexcept;

  virtual NodeLnk * Skip2Left(NodeLnk *&) noexcept;
  virtual NodeLnk * Skip2Right(NodeLnk *&) noexcept;

  virtual NodeLnk *& FindPointerToMin(NodeLnk *&) noexcept;
  virtual const NodeLnk * const & FindPointerToMin(const NodeLnk * const &) const noexcept;
  virtual NodeLnk *& FindPointerToMax(NodeLnk *&) noexcept;
  virtual const NodeLnk * const & FindPointerToMax(const NodeLnk * const &) const noexcept;

  virtual NodeLnk *& FindPointerTo(NodeLnk *&, const Data &) noexcept;
  virtual const NodeLnk * const & FindPointerTo(const NodeLnk * const &, const Data &) const noexcept;

  virtual NodeLnk ** FindPointerToPredecessor(NodeLnk *&, const Data &) noexcept;
  virtual const NodeLnk * const * FindPointerToPredecessor(const NodeLnk * const &, const Data &) const noexcept;
  virtual NodeLnk ** FindPointerToSuccessor(NodeLnk *&, const Data &) noexcept;
  virtual const NodeLnk * const * FindPointerToSuccessor(const NodeLnk * const &, const Data &) const noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
