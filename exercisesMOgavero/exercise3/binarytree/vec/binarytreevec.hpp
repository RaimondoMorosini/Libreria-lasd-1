
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data>,
  virtual protected Vector<Data> {

private:

protected:

  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;

protected:

  struct NodeVec : virtual MutableNode {

    BinaryTreeVec * Tree = nullptr;

    /* ********************************************************************** */

    // Default constructor
    NodeVec() = default;

    /* ********************************************************************** */

    // Destructor
    virtual ~NodeVec() = default;

    /* ********************************************************************** */

    // Specific member functions (inherited from Node)

    inline const Data & Element() const noexcept override;
    inline Data & Element() noexcept override;

    inline bool IsLeaf() const noexcept override;
    inline bool HasLeftChild() const noexcept override;
    inline bool HasRightChild() const noexcept override;

    virtual const Node & LeftChild() const override;

    virtual const Node & RightChild() const override;

    /* ********************************************************************** */

    // Specific member functions (inherited from MutableNode)

    virtual MutableNode & LeftChild() override;

    virtual MutableNode & RightChild() override;

  protected:

    // Auxiliary member function

    virtual ulong Index() const noexcept;

  };

  NodeVec * Nodes = nullptr;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data> &);
  BinaryTreeVec(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec &);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec & operator=(const BinaryTreeVec &);

  // Move assignment
  BinaryTreeVec & operator=(BinaryTreeVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  using BinaryTree<Data>::operator==;
  inline bool operator==(const BinaryTreeVec &) const noexcept;
  using BinaryTree<Data>::operator!=;
  inline bool operator!=(const BinaryTreeVec &) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)

  const Node & Root() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  MutableNode & Root() override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthTraversableContainer)

  inline void BreadthTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)

  inline void BreadthMap(MapFun) override;

protected:

  // Auxiliary member functions

  virtual void NewNodeArray();
  virtual void SwapNodeArrays(BinaryTreeVec &&) noexcept;

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
