
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public MutableBinaryTree<Data> {

private:

protected:

  using Container::size;

public:

  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;

protected:

  struct NodeLnk : virtual MutableNode {

    // friend class BinaryTreeLnk<Data>;

    /* ********************************************************************** */

    NodeLnk * left = nullptr;
    NodeLnk * right = nullptr;
    Data element;

    /* ********************************************************************** */

    // Specific constructors

    NodeLnk(const Data & dat) noexcept : element(dat) {};
    NodeLnk(Data && dat) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    NodeLnk(const NodeLnk &);

    // Move constructor
    NodeLnk(NodeLnk &&) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~NodeLnk();

    /* ********************************************************************** */

    // Copy assignment
    NodeLnk & operator=(const NodeLnk &);

    // Move assignment
    NodeLnk & operator=(NodeLnk &&) noexcept;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const NodeLnk &) const noexcept;
    inline bool operator!=(const NodeLnk &) const noexcept;

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

  };

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data> &);
  BinaryTreeLnk(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk &);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk & operator=(const BinaryTreeLnk &);

  // Move assignment
  BinaryTreeLnk & operator=(BinaryTreeLnk &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  using BinaryTree<Data>::operator==;
  inline bool operator==(const BinaryTreeLnk &) const noexcept;
  using BinaryTree<Data>::operator!=;
  inline bool operator!=(const BinaryTreeLnk &) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)

  const Node & Root() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  MutableNode & Root() override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

protected:

  NodeLnk * root = nullptr;

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
