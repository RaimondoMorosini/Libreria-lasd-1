
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
#include "../queue/vec/queuevec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : virtual public ClearableContainer,
  virtual public PreOrderTraversableContainer<Data>,
  virtual public PostOrderTraversableContainer<Data>,
  virtual public InOrderTraversableContainer<Data>,
  virtual public BreadthTraversableContainer<Data> {

private:

protected:

  using Container::size;

public:

  struct Node {

  protected:

    // Comparison operators
    bool operator==(const Node &) const noexcept;
    inline bool operator!=(const Node &) const noexcept;

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node & operator=(const Node &) = delete;

    // Move assignment
    Node & operator=(Node &&) noexcept = delete;

    /* ********************************************************************** */

    // Specific member functions

    virtual const Data & Element() const noexcept = 0;

    inline virtual bool IsLeaf() const noexcept;
    virtual bool HasLeftChild() const noexcept = 0;
    virtual bool HasRightChild() const noexcept = 0;

    virtual const Node & LeftChild() const = 0;

    virtual const Node & RightChild() const = 0;

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree & operator=(const BinaryTree &) = delete;

  // Move assignment
  BinaryTree & operator=(BinaryTree &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  inline virtual bool operator==(const BinaryTree &) const noexcept;
  inline virtual bool operator!=(const BinaryTree &) const noexcept;

  /* ************************************************************************ */

  // Specific member function

  virtual const Node & Root() const = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  inline void InOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  inline void BreadthTraverse(TraverseFun) const override;

protected:

  // Auxiliary member function (for PreOrderMappableContainer)

  virtual void PreOrderTraverse(TraverseFun, const Node &) const;

  /* ************************************************************************ */

  // Auxiliary member function (for PostOrderMappableContainer)

  virtual void PostOrderTraverse(TraverseFun, const Node &) const;

  /* ************************************************************************ */

  // Auxiliary member function (for InOrderMappableContainer)

  virtual void InOrderTraverse(TraverseFun, const Node &) const;

  /* ************************************************************************ */

  // Auxiliary member function (for BreadthMappableContainer)

  virtual void BreadthTraverse(TraverseFun, const Node &) const;

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : virtual public BinaryTree<Data>,
  virtual public PreOrderMappableContainer<Data>,
  virtual public PostOrderMappableContainer<Data>,
  virtual public InOrderMappableContainer<Data>,
  virtual public BreadthMappableContainer<Data> {

private:

protected:

  using Container::size;

  using typename BinaryTree<Data>::Node;

public:

  struct MutableNode : Node {

    // Destructor
    virtual ~MutableNode() = default;

    /* ********************************************************************** */

    // Copy assignment
    MutableNode & operator=(const MutableNode &) = delete;

    // Move assignment
    MutableNode & operator=(MutableNode &&) noexcept = delete;

    /* ********************************************************************** */

    // Specific member functions

    using Node::Element;
    virtual Data & Element() noexcept = 0;

    using Node::LeftChild;
    virtual MutableNode & LeftChild() = 0;

    using Node::RightChild;
    virtual MutableNode & RightChild() = 0;

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableBinaryTree & operator=(const MutableBinaryTree &) = delete;

  // Move assignment
  MutableBinaryTree & operator=(MutableBinaryTree &&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using BinaryTree<Data>::Root;
  virtual MutableNode & Root() = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  inline void InOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  inline void BreadthMap(MapFun) override;

protected:

  // Auxiliary member function (for PreOrderMappableContainer)

  virtual void PreOrderMap(MapFun, MutableNode &);

  /* ************************************************************************ */

  // Auxiliary member function (for PostOrderMappableContainer)

  virtual void PostOrderMap(MapFun, MutableNode &);

  /* ************************************************************************ */

  // Auxiliary member function (for InOrderMappableContainer)

  virtual void InOrderMap(MapFun, MutableNode &);

  /* ************************************************************************ */

  // Auxiliary member function (for BreadthMappableContainer)

  virtual void BreadthMap(MapFun, MutableNode &);

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>,
  virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  StackVec<const typename BinaryTree<Data>::Node *> stk;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data> & bt) {
    if (bt.Size() != 0) {
      stk.Push(root = &bt.Root());
    }
  };

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator & itr) : root(itr.root), stk(itr.stk) {}

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator && itr) noexcept {
    std::swap(root, itr.root);
    std::swap(stk, itr.stk);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator & operator=(const BTPreOrderIterator & itr) {
    root = itr.root;
    stk = itr.stk;
    return *this;
  }

  // Move assignment
  BTPreOrderIterator & operator=(BTPreOrderIterator && itr) noexcept {
    std::swap(root, itr.root);
    std::swap(stk, itr.stk);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTPreOrderIterator &) const noexcept = default;
  inline bool operator!=(const BTPreOrderIterator &) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override {
    if (!stk.Empty()) {
      return stk.Top()->Element();
    } else {
      throw std::out_of_range("The iterator is terminated.");
    }
  };

  bool Terminated() const noexcept override {
    return stk.Empty();
  };

  /* ************************************************************************ */

  // Specific member function (inherited from ForwardIterator)

  ForwardIterator<Data> & operator++() override {
    const typename BinaryTree<Data>::Node & curr = *stk.TopNPop();
    if (curr.HasRightChild()) {
      stk.Push(&curr.RightChild());
    }
    if (curr.HasLeftChild()) {
      stk.Push(&curr.LeftChild());
    }
    return *this;
  };

  /* ************************************************************************ */

  // Specific member function (inherited from ResettableIterator)

  void Reset() noexcept override {
    if (root != nullptr) {
      stk.Clear();
      stk.Push(root);
    }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : virtual public MutableIterator<Data>,
  virtual public BTPreOrderIterator<Data> {

private:

protected:

  using BTPreOrderIterator<Data>::stk;

public:

  // Specific constructors
  BTPreOrderMutableIterator(MutableBinaryTree<Data> & bt) : BTPreOrderIterator<Data>(bt) {};

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator & itr) : BTPreOrderIterator<Data>(itr) {};

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator && itr) noexcept : BTPreOrderIterator<Data>(std::move(itr)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator & operator=(const BTPreOrderMutableIterator & itr) {
    BTPreOrderIterator<Data>::operator=(itr);
  }

  // Move assignment
  BTPreOrderMutableIterator & operator=(BTPreOrderMutableIterator && itr) noexcept {
    BTPreOrderIterator<Data>::operator=(std::move(itr));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data & operator*() override {
    if (!stk.Empty()) {
      return const_cast<Data &>(stk.Top()->Element());
    } else {
      throw std::out_of_range("The iterator is terminated.");
    }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>,
  virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  StackVec<const typename BinaryTree<Data>::Node *> stk;

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data> & bt) {
    if (bt.Size() != 0) {
      stk.Push(root = &bt.Root());
      SearchLeftMostLeaf();
    }
  };

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator & itr) : root(itr.root), stk(itr.stk) {}

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator && itr) noexcept {
    std::swap(root, itr.root);
    std::swap(stk, itr.stk);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator & operator=(const BTPostOrderIterator & itr) {
    root = itr.root;
    stk = itr.stk;
    return *this;
  }

  // Move assignment
  BTPostOrderIterator & operator=(BTPostOrderIterator && itr) noexcept {
    std::swap(root, itr.root);
    std::swap(stk, itr.stk);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTPostOrderIterator &) const noexcept = default;
  inline bool operator!=(const BTPostOrderIterator &) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override {
    if (!stk.Empty()) {
      return stk.Top()->Element();
    } else {
      throw std::out_of_range("The iterator is terminated.");
    }
  };

  bool Terminated() const noexcept override {
    return stk.Empty();
  };

  /* ************************************************************************ */

  // Specific member function (inherited from ForwardIterator)

  ForwardIterator<Data> & operator++() override {
    const typename BinaryTree<Data>::Node * last = stk.TopNPop();
    if (!stk.Empty()) {
      const typename BinaryTree<Data>::Node & top = *stk.Top();
      if (top.HasRightChild() && (last != &top.RightChild())) {
        stk.Push(&top.RightChild());
        SearchLeftMostLeaf();
      }
    };
    return *this;
  }

  /* ************************************************************************ */

  // Specific member function (inherited from ResettableIterator)

  void Reset() noexcept override {
    if (root != nullptr) {
      stk.Clear();
      stk.Push(root);
      SearchLeftMostLeaf();
    }
  };

protected:

  // Auxiliary member function

  void SearchLeftMostLeaf() {
    const typename BinaryTree<Data>::Node * curr;
    while (true) {
      while ((curr = stk.Top())->HasLeftChild()) {
        stk.Push(&curr->LeftChild());
      }
      if (curr->HasRightChild()) {
        stk.Push(&curr->RightChild());
      } else {
        break;
      }
    }
  }

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : virtual public MutableIterator<Data>,
  virtual public BTPostOrderIterator<Data> {

private:

protected:

  using BTPostOrderIterator<Data>::stk;

public:

  // Specific constructors
  BTPostOrderMutableIterator(MutableBinaryTree<Data> & bt) : BTPostOrderIterator<Data>(bt) {};

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator & itr) : BTPostOrderIterator<Data>(itr) {};

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator && itr) noexcept : BTPostOrderIterator<Data>(std::move(itr)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator & operator=(const BTPostOrderMutableIterator & itr) {
    BTPostOrderIterator<Data>::operator=(itr);
  }

  // Move assignment
  BTPostOrderMutableIterator & operator=(BTPostOrderMutableIterator && itr) noexcept {
    BTPostOrderIterator<Data>::operator=(std::move(itr));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data & operator*() override {
    if (!stk.Empty()) {
      return const_cast<Data &>(stk.Top()->Element());
    } else {
      throw std::out_of_range("The iterator is terminated.");
    }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>,
  virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  StackVec<const typename BinaryTree<Data>::Node *> stk;

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data> & bt) {
    if (bt.Size() != 0) {
      stk.Push(root = &bt.Root());
      SearchLeftMostNode();
    }
  };

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator & itr) : root(itr.root), stk(itr.stk) {}

  // Move constructor
  BTInOrderIterator(BTInOrderIterator && itr) noexcept {
    std::swap(root, itr.root);
    std::swap(stk, itr.stk);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator & operator=(const BTInOrderIterator & itr) {
    root = itr.root;
    stk = itr.stk;
    return *this;
  }

  // Move assignment
  BTInOrderIterator & operator=(BTInOrderIterator && itr) noexcept {
    std::swap(root, itr.root);
    std::swap(stk, itr.stk);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTInOrderIterator &) const noexcept = default;
  inline bool operator!=(const BTInOrderIterator &) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override {
    if (!stk.Empty()) {
      return stk.Top()->Element();
    } else {
      throw std::out_of_range("The iterator is terminated.");
    }
  };

  bool Terminated() const noexcept override {
    return stk.Empty();
  };

  /* ************************************************************************ */

  // Specific member function (inherited from ForwardIterator)

  ForwardIterator<Data> & operator++() override {
    const typename BinaryTree<Data>::Node & curr = *stk.TopNPop();
    if (curr.HasRightChild()) {
      stk.Push(&curr.RightChild());
      SearchLeftMostNode();
    }
    return *this;
  };

  /* ************************************************************************ */

  // Specific member function (inherited from ResettableIterator)

  void Reset() noexcept override {
    if (root != nullptr) {
      stk.Clear();
      stk.Push(root);
      SearchLeftMostNode();
    }
  };

protected:

  // Auxiliary member function

  void SearchLeftMostNode() {
    const typename BinaryTree<Data>::Node * curr;
    while ((curr = stk.Top())->HasLeftChild()) {
      stk.Push(&curr->LeftChild());
    }
  }

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator : virtual public MutableIterator<Data>,
  virtual public BTInOrderIterator<Data> {

private:

protected:

  using BTInOrderIterator<Data>::stk;

public:

  // Specific constructors
  BTInOrderMutableIterator(MutableBinaryTree<Data> & bt) : BTInOrderIterator<Data>(bt) {};

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator & itr) : BTInOrderIterator<Data>(itr) {};

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator && itr) noexcept : BTInOrderIterator<Data>(std::move(itr)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator & operator=(const BTInOrderMutableIterator & itr) {
    BTInOrderIterator<Data>::operator=(itr);
  }

  // Move assignment
  BTInOrderMutableIterator & operator=(BTInOrderMutableIterator && itr) noexcept {
    BTInOrderIterator<Data>::operator=(std::move(itr));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data & operator*() override {
    if (!stk.Empty()) {
      return const_cast<Data &>(stk.Top()->Element());
    } else {
      throw std::out_of_range("The iterator is terminated.");
    }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>,
  virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  QueueVec<const typename BinaryTree<Data>::Node *> que;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data> & bt) {
    if (bt.Size() != 0) {
      que.Enqueue(root = &bt.Root());
    }
  };

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator & itr) : root(itr.root), que(itr.que) {}

  // Move constructor
  BTBreadthIterator(BTBreadthIterator && itr) noexcept {
    std::swap(root, itr.root);
    std::swap(que, itr.que);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator & operator=(const BTBreadthIterator & itr) {
    root = itr.root;
    que = itr.que;
    return *this;
  }

  // Move assignment
  BTBreadthIterator & operator=(BTBreadthIterator && itr) noexcept {
    std::swap(root, itr.root);
    std::swap(que, itr.que);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTBreadthIterator &) const noexcept = default;
  inline bool operator!=(const BTBreadthIterator &) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override {
    if (!que.Empty()) {
      return que.Head()->Element();
    } else {
      throw std::out_of_range("The iterator is terminated.");
    }
  };

  bool Terminated() const noexcept override {
    return que.Empty();
  };

  /* ************************************************************************ */

  // Specific member function (inherited from ForwardIterator)

  ForwardIterator<Data> & operator++() override {
    const typename BinaryTree<Data>::Node & curr = *que.HeadNDequeue();
    if (curr.HasLeftChild()) {
      que.Enqueue(&curr.LeftChild());
    }
    if (curr.HasRightChild()) {
      que.Enqueue(&curr.RightChild());
    }
    return *this;
  };

  /* ************************************************************************ */

  // Specific member function (inherited from ResettableIterator)

  void Reset() noexcept override {
    if (root != nullptr) {
      que.Clear();
      que.Enqueue(root);
    }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : virtual public MutableIterator<Data>,
  virtual public BTBreadthIterator<Data> {

private:

protected:

  using BTBreadthIterator<Data>::que;

public:

  // Specific constructors
  BTBreadthMutableIterator(MutableBinaryTree<Data> & bt) : BTBreadthIterator<Data>(bt) {};

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator & itr) : BTBreadthIterator<Data>(itr) {};

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator && itr) noexcept : BTBreadthIterator<Data>(std::move(itr)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator & operator=(const BTBreadthMutableIterator & itr) {
    BTBreadthIterator<Data>::operator=(itr);
  }

  // Move assignment
  BTBreadthMutableIterator & operator=(BTBreadthMutableIterator && itr) noexcept {
    BTBreadthIterator<Data>::operator=(std::move(itr));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data & operator*() override {
    if (!que.Empty()) {
      return const_cast<Data &>(que.Head()->Element());
    } else {
      throw std::out_of_range("The iterator is terminated.");
    }
  };

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
