
namespace lasd {

/* ************************************************************************** */

// Specific constructors (BST)

template<typename Data>
BST<Data>::BST(const TraversableContainer<Data> & con) {
  con.Traverse(
    [this](const Data & dat) {
      Insert(dat);
    }
  );
}

template<typename Data>
BST<Data>::BST(MappableContainer<Data> && con) {
  con.Map(
    [this](Data & dat) {
      Insert(std::move(dat));
    }
  );
}

/* ************************************************************************** */

// Copy assignment (BST)
template<typename Data>
BST<Data> & BST<Data>::operator=(const BST<Data> & bst) {
  BinaryTreeLnk<Data>::operator=(bst);
  return *this;
}

// Move assignment (BST)
template<typename Data>
BST<Data> & BST<Data>::operator=(BST<Data> && bst) noexcept {
  BinaryTreeLnk<Data>::operator=(std::move(bst));
  return *this;
}

/* ************************************************************************** */

// Comparison operators (BST)

template<typename Data>
inline bool BST<Data>::operator==(const BST<Data> & bst) const noexcept {
  if (size == bst.Size()) {
    BTInOrderIterator<Data> itr1(*this);
    BTInOrderIterator<Data> itr2(bst);
    for (; !itr1.Terminated(); ++itr1, ++itr2) {
      if (*itr1 != *itr2) {
        return false;
      }
    }
    return true;
  }
  return false;
}

template<typename Data>
inline bool BST<Data>::operator!=(const BST<Data> & bst) const noexcept {
  return !(*this == bst);
}

/* ************************************************************************** */

// Specific member functions (BST)

template<typename Data>
const Data & BST<Data>::Min() const {
  if (root != nullptr) {
    return FindPointerToMin(root)->element;
  } else {
    throw std::length_error("Access to an empty tree.");
  }
}

template<typename Data>
Data BST<Data>::MinNRemove() {
  if (root != nullptr) {
    return DataNDelete(DetachMin(root));
  } else {
    throw std::length_error("Access to an empty tree.");
  }
}

template<typename Data>
void BST<Data>::RemoveMin() {
  if (root != nullptr) {
    delete DetachMin(root);
  } else {
    throw std::length_error("Access to an empty tree.");
  }
}

template<typename Data>
const Data & BST<Data>::Max() const {
  if (root != nullptr) {
    return FindPointerToMax(root)->element;
  } else {
    throw std::length_error("Access to an empty tree.");
  }
}

template<typename Data>
Data BST<Data>::MaxNRemove() {
  if (root != nullptr) {
    return DataNDelete(DetachMax(root));
  } else {
    throw std::length_error("Access to an empty tree.");
  }
}

template<typename Data>
void BST<Data>::RemoveMax() {
  if (root != nullptr) {
    delete DetachMax(root);
  } else {
    throw std::length_error("Access to an empty tree.");
  }
}

template<typename Data>
const Data & BST<Data>::Predecessor(const Data & dat) const {
  const NodeLnk * const * ptr = FindPointerToPredecessor(root, dat);
  if (ptr != nullptr) {
    return (*ptr)->element;
  } else {
    throw std::length_error("Predecessor out of bound.");
  }
}

template<typename Data>
Data BST<Data>::PredecessorNRemove(const Data & dat) {
  NodeLnk ** ptr = FindPointerToPredecessor(root, dat);
  if (ptr != nullptr) {
    return DataNDelete(Detach(*ptr));
  } else {
    throw std::length_error("Predecessor out of bound.");
  }
}

template<typename Data>
void BST<Data>::RemovePredecessor(const Data & dat) {
  NodeLnk ** ptr = FindPointerToPredecessor(root, dat);
  if (ptr != nullptr) {
    delete Detach(*ptr);
  } else {
    throw std::length_error("Predecessor out of bound.");
  }
}

template<typename Data>
const Data & BST<Data>::Successor(const Data & dat) const {
  const NodeLnk * const * ptr = FindPointerToSuccessor(root, dat);
  if (ptr != nullptr) {
    return (*ptr)->element;
  } else {
    throw std::length_error("Successor out of bound.");
  }
}

template<typename Data>
Data BST<Data>::SuccessorNRemove(const Data & dat) {
  NodeLnk ** ptr = FindPointerToSuccessor(root, dat);
  if (ptr != nullptr) {
    return DataNDelete(Detach(*ptr));
  } else {
    throw std::length_error("Successor out of bound.");
  }
}

template<typename Data>
void BST<Data>::RemoveSuccessor(const Data & dat) {
  NodeLnk ** ptr = FindPointerToSuccessor(root, dat);
  if (ptr != nullptr) {
    delete Detach(*ptr);
  } else {
    throw std::length_error("Successor out of bound.");
  }
}

/* ************************************************************************** */

// Specific member functions (BST) (inherited from TestableContainer)

template<typename Data>
bool BST<Data>::Exists(const Data & dat) const noexcept {
  return (FindPointerTo(root, dat) != nullptr);
}

/* ************************************************************************** */

// Specific member functions (BST) (inherited from DictionaryContainer)

template<typename Data>
bool BST<Data>::Insert(const Data & dat) {
  NodeLnk *& ptr = FindPointerTo(root, dat);
  if (ptr == nullptr) {
    ptr = new NodeLnk(dat);
    size++;
    return true;
  }
  return false;
}

template<typename Data>
bool BST<Data>::Insert(Data && dat) {
  NodeLnk *& ptr = FindPointerTo(root, dat);
  if (ptr == nullptr) {
    ptr = new NodeLnk(std::move(dat));
    size++;
    return true;
  }
  return false;
}

template<typename Data>
bool BST<Data>::Remove(const Data & dat) {
  NodeLnk *& ptr = FindPointerTo(root, dat);
  if (ptr != nullptr) {
    delete Detach(ptr);
    return true;
  }
  return false;
}

/* ************************************************************************** */

// Auxiliary member functions (BST)

template<typename Data>
Data BST<Data>::DataNDelete(NodeLnk * ptr) {
  Data dat {};
  std::swap(dat, ptr->element);
  delete ptr;
  return dat;
}

template<typename Data>
typename BST<Data>::NodeLnk * BST<Data>::Detach(NodeLnk *& nod) noexcept {
  if (nod != nullptr) {
    if (nod->left == nullptr) {
      return Skip2Right(nod);
    } else if (nod->right == nullptr) {
      return Skip2Left(nod);
    } else {
      NodeLnk * max = DetachMax(nod->left);
      std::swap(nod->element, max->element);
      return max;
    }
  }
  return nullptr;
}

template<typename Data>
typename BST<Data>::NodeLnk * BST<Data>::DetachMin(NodeLnk *& nod) noexcept {
  return Skip2Right(FindPointerToMin(nod));
}

template<typename Data>
typename BST<Data>::NodeLnk * BST<Data>::DetachMax(NodeLnk *& nod) noexcept {
  return Skip2Left(FindPointerToMax(nod));
}

template<typename Data>
typename BST<Data>::NodeLnk * BST<Data>::Skip2Left(NodeLnk *& nod) noexcept {
  NodeLnk * lef = nullptr;
  if (nod != nullptr) {
    std::swap(lef, nod->left);
    std::swap(lef, nod);
    --size;
  }
  return lef;
}

template<typename Data>
typename BST<Data>::NodeLnk * BST<Data>::Skip2Right(NodeLnk *& nod) noexcept {
  NodeLnk * rig = nullptr;
  if (nod != nullptr) {
    std::swap(rig, nod->right);
    std::swap(rig, nod);
    --size;
  }
  return rig;
}

template<typename Data>
typename BST<Data>::NodeLnk *& BST<Data>::FindPointerToMin(NodeLnk *& nod) noexcept {
  return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(nod));
}

template<typename Data>
const typename BST<Data>::NodeLnk * const & BST<Data>::FindPointerToMin(const NodeLnk * const & nod) const noexcept {
  const NodeLnk * const * ptr = &nod;
  const NodeLnk * cur = nod;
  if (cur != nullptr) {
    while (cur->left != nullptr) {
      ptr = &cur->left;
      cur = cur->left;
    }
  }
  return *ptr;
}

template<typename Data>
typename BST<Data>::NodeLnk *& BST<Data>::FindPointerToMax(NodeLnk *& nod) noexcept {
  return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(nod));
}

template<typename Data>
const typename BST<Data>::NodeLnk * const & BST<Data>::FindPointerToMax(const NodeLnk * const & nod) const noexcept {
  const NodeLnk * const * ptr = &nod;
  const NodeLnk * cur = nod;
  if (cur != nullptr) {
    while (cur->right != nullptr) {
      ptr = &cur->right;
      cur = cur->right;
    }
  }
  return *ptr;
}

template<typename Data>
inline typename BST<Data>::NodeLnk *& BST<Data>::FindPointerTo(NodeLnk *& nod, const Data & dat) noexcept {
  return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerTo(nod, dat));
}

template<typename Data>
const typename BST<Data>::NodeLnk * const & BST<Data>::FindPointerTo(const NodeLnk * const & nod, const Data & dat) const noexcept {
  const NodeLnk * const * ptr = &nod;
  const NodeLnk * cur = nod;
  while (cur != nullptr) {
    if (cur->element < dat) {
      ptr = &cur->right;
      cur = cur->right;
    } else if (cur->element > dat) {
      ptr = &cur->left;
      cur = cur->left;
    } else {
      break;
    }
  }
  return *ptr;
}

template<typename Data>
typename BST<Data>::NodeLnk ** BST<Data>::FindPointerToPredecessor(NodeLnk *& nod, const Data & dat) noexcept {
  return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(nod, dat));
}

template<typename Data>
const typename BST<Data>::NodeLnk * const * BST<Data>::FindPointerToPredecessor(const NodeLnk * const & nod, const Data & dat) const noexcept {
  const NodeLnk * const * ptr = &nod;
  const NodeLnk * const * prd = nullptr;
  while (true) {
    const NodeLnk & cur = **ptr;
    if (cur.element < dat) {
      prd = ptr;
      if (cur.right == nullptr) {
        return prd;
      } else {
        ptr = &cur.right;
      }
    } else {
      if (cur.left == nullptr) {
        return prd;
      } else {
        if (cur.element > dat) {
          ptr = &cur.left;
        } else {
          return &FindPointerToMax(cur.left);
        }
      }
    }
  }
}

template<typename Data>
typename BST<Data>::NodeLnk ** BST<Data>::FindPointerToSuccessor(NodeLnk *& nod, const Data & dat) noexcept {
  return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(nod, dat));
}

template<typename Data>
const typename BST<Data>::NodeLnk * const * BST<Data>::FindPointerToSuccessor(const NodeLnk * const & nod, const Data & dat) const noexcept {
  const NodeLnk * const * ptr = &nod;
  const NodeLnk * const * prd = nullptr;
  while (true) {
    const NodeLnk & cur = **ptr;
    if (cur.element > dat) {
      prd = ptr;
      if (cur.left == nullptr) {
        return prd;
      } else {
        ptr = &cur.left;
      }
    } else {
      if (cur.right == nullptr) {
        return prd;
      } else {
        if (cur.element < dat) {
          ptr = &cur.right;
        } else {
          return &FindPointerToMin(cur.right);
        }
      }
    }
  }
}

/* ************************************************************************** */

}
