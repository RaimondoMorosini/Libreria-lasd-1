
#include "../queue/lst/queuelst.hpp"

namespace lasd {

/* ************************************************************************** */

// Comparison operators (Node)

template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node & nod) const noexcept {
  return (Element() == nod.Element()) \
    && (((!HasLeftChild() && !nod.HasLeftChild()) || ((HasLeftChild() && nod.HasLeftChild()) && (LeftChild() == nod.LeftChild()))) \
      && ((!HasRightChild() && !nod.HasRightChild()) || ((HasRightChild() && nod.HasRightChild()) && (RightChild() == nod.RightChild()))));
}

template <typename Data>
inline bool BinaryTree<Data>::Node::operator!=(const Node & nod) const noexcept {
  return !(*this == nod);
}

/* ************************************************************************** */

// Specific member functions (Node)
template <typename Data>
inline bool BinaryTree<Data>::Node::IsLeaf() const noexcept {
  return !(HasLeftChild() || HasRightChild());
}

/* ************************************************************************** */

// Comparison operators (BinaryTree)

template<typename Data>
inline bool BinaryTree<Data>::operator==(const BinaryTree<Data> & bt) const noexcept {
  return (size == bt.size) && (size == 0 || (size != 0 && (Root() == bt.Root())));
}

template<typename Data>
inline bool BinaryTree<Data>::operator!=(const BinaryTree<Data> & bt) const noexcept {
  return !(*this == bt);
}

/* ************************************************************************** */

// Specific member functions (BinaryTree) (inherited from TraversableContainer)

template<typename Data>
inline void BinaryTree<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun);
}

/* ************************************************************************** */

// Specific member functions (BinaryTree) (inherited from PreOrderTraversableContainer)

template<typename Data>
inline void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun) const {
  if (size > 0) {
    PreOrderTraverse(fun, Root());
  }
}

/* ************************************************************************** */

// Specific member functions (BinaryTree) (inherited from PostOrderTraversableContainer)

template<typename Data>
inline void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun) const {
  if (size > 0) {
    PostOrderTraverse(fun, Root());
  }
}

/* ************************************************************************** */

// Specific member functions (BinaryTree) (inherited from InOrderTraversableContainer)

template<typename Data>
inline void BinaryTree<Data>::InOrderTraverse(TraverseFun fun) const {
  if (size > 0) {
    InOrderTraverse(fun, Root());
  }
}

/* ************************************************************************** */

// Specific member functions (BinaryTree) (inherited from BreadthTraversableContainer)

template<typename Data>
inline void BinaryTree<Data>::BreadthTraverse(TraverseFun fun) const {
  if (size > 0) {
    BreadthTraverse(fun, Root());
  }
}

/* ************************************************************************** */

// Auxiliary member functions (BinaryTree) (for PreOrderTraversableContainer)

template<typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun, const Node & nod) const {
  fun(nod.Element());
  if (nod.HasLeftChild()) {
    PreOrderTraverse(fun, nod.LeftChild());
  }
  if (nod.HasRightChild()) {
    PreOrderTraverse(fun, nod.RightChild());
  }
}

/* ************************************************************************** */

// Auxiliary member functions (BinaryTree) (for PostOrderTraversableContainer)

template<typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun, const Node & nod) const {
  if (nod.HasLeftChild()) {
    PostOrderTraverse(fun, nod.LeftChild());
  }
  if (nod.HasRightChild()) {
    PostOrderTraverse(fun, nod.RightChild());
  }
  fun(nod.Element());
}

/* ************************************************************************** */

// Auxiliary member functions (BinaryTree) (for InOrderTraversableContainer)

template<typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun fun, const Node & nod) const {
  if (nod.HasLeftChild()) {
    InOrderTraverse(fun, nod.LeftChild());
  }
  fun(nod.Element());
  if (nod.HasRightChild()) {
    InOrderTraverse(fun, nod.RightChild());
  }
}

/* ************************************************************************** */

// Auxiliary member functions (BinaryTree) (for BreadthTraversableContainer)

template<typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun fun, const Node & nod) const {
  QueueVec<const Node *> Queue;
  Queue.Enqueue(&nod);
  while (!Queue.Empty()) {
    const Node & cur = *Queue.HeadNDequeue();
    fun(cur.Element());
    if (cur.HasLeftChild()) {
      Queue.Enqueue(&cur.LeftChild());
    }
    if (cur.HasRightChild()) {
      Queue.Enqueue(&cur.RightChild());
    }
  }
}

/* ************************************************************************** */

// Specific member functions (MutableBinaryTree) (inherited from MappableContainer)

template<typename Data>
inline void MutableBinaryTree<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member functions (MutableBinaryTree) (inherited from PreOrderMappableContainer)

template<typename Data>
inline void MutableBinaryTree<Data>::PreOrderMap(MapFun fun) {
  if (size > 0) {
    PreOrderMap(fun, Root());
  }
}

/* ************************************************************************** */

// Specific member functions (MutableBinaryTree) (inherited from PostOrderMappableContainer)

template<typename Data>
inline void MutableBinaryTree<Data>::PostOrderMap(MapFun fun) {
  if (size > 0) {
    PostOrderMap(fun, Root());
  }
}

/* ************************************************************************** */

// Specific member functions (MutableBinaryTree) (inherited from InOrderMappableContainer)

template<typename Data>
inline void MutableBinaryTree<Data>::InOrderMap(MapFun fun) {
  if (size > 0) {
    InOrderMap(fun, Root());
  }
}

/* ************************************************************************** */

// Specific member functions (MutableBinaryTree) (inherited from BreadthMappableContainer)

template<typename Data>
inline void MutableBinaryTree<Data>::BreadthMap(MapFun fun) {
  if (size > 0) {
    BreadthMap(fun, Root());
  }
}

/* ************************************************************************** */

// Auxiliary member functions (MutableBinaryTree) (for PreOrderMappableContainer)

template<typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun fun, MutableNode & nod) {
  fun(nod.Element());
  if (nod.HasLeftChild()) {
    PreOrderMap(fun, nod.LeftChild());
  }
  if (nod.HasRightChild()) {
    PreOrderMap(fun, nod.RightChild());
  }
}

/* ************************************************************************** */

// Auxiliary member functions (MutableBinaryTree) (for PostOrderMappableContainer)

template<typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun fun, MutableNode & nod) {
  if (nod.HasLeftChild()) {
    PostOrderMap(fun, nod.LeftChild());
  }
  if (nod.HasRightChild()) {
    PostOrderMap(fun, nod.RightChild());
  }
  fun(nod.Element());
}

/* ************************************************************************** */

// Auxiliary member functions (MutableBinaryTree) (for InOrderMappableContainer)

template<typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun fun, MutableNode & nod) {
  if (nod.HasLeftChild()) {
    InOrderMap(fun, nod.LeftChild());
  }
  fun(nod.Element());
  if (nod.HasRightChild()) {
    InOrderMap(fun, nod.RightChild());
  }
}

/* ************************************************************************** */

// Auxiliary member functions (MutableBinaryTree) (for BreadthMappableContainer)

template<typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun fun, MutableNode & nod) {
  QueueLst<MutableNode *> Queue;
  Queue.Enqueue(&nod);
  while (!Queue.Empty()) {
    MutableNode & cur = *Queue.HeadNDequeue();
    fun(cur.Element());
    if (cur.HasLeftChild()) {
      Queue.Enqueue(&cur.LeftChild());
    }
    if (cur.HasRightChild()) {
      Queue.Enqueue(&cur.RightChild());
    }
  }
}

/* ************************************************************************** */

}
