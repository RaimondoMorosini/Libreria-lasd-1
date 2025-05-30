
namespace lasd {

/* ************************************************************************** */

// Comparison operators (LinearContainer)

template<typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data> & con) const noexcept {
  if (this->Size() == con.Size()) {
    for (ulong index = 0; index < this->Size(); ++index) {
      if (operator[](index) != con.operator[](index)) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}

template<typename Data>
inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data> & con) const noexcept {
  return !(*this == con);
}

/* ************************************************************************** */

// Specific member functions (LinearContainer)

template <typename Data>
inline const Data & LinearContainer<Data>::Front() const {
  return operator[](0);
}


template <typename Data>
inline const Data & LinearContainer<Data>::Back() const {
  return operator[](this->Size() - 1);
}


/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from TraversableContainer)

template<typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun);
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PreOrderTraversableContainer)

template<typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
  for (ulong index = 0; index < this->Size(); ++index) {
    fun(operator[](index));
  }
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PostOrderTraversableContainer)

template<typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
  ulong index = this->Size();
  while (index > 0) {
    fun(operator[](--index));
  }
}

/* ************************************************************************** */

// Specific member functions (MutableContainer)


template <typename Data>
inline Data & MutableLinearContainer<Data>::Front() {
  return operator[](0);
}


template <typename Data>
inline Data & MutableLinearContainer<Data>::Back() {
  return operator[](this->Size() - 1);
}



// Comparison operators (MutableContainer)

template<typename Data>
bool MutableLinearContainer<Data>::operator==(const MutableLinearContainer<Data> & con) const noexcept {
  return LinearContainer<Data>::operator==(con);
}

template<typename Data>
inline bool MutableLinearContainer<Data>::operator!=(const MutableLinearContainer<Data> & con) const noexcept {
  return LinearContainer<Data>::operator!=(con);
}



/* ************************************************************************** */

// Specific member functions (MutableContainer) (inherited from MappableContainer)

template<typename Data>
inline void MutableLinearContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member functions (MutableContainer) (inherited from PreOrderMappableContainer)

template<typename Data>
inline void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
  for (ulong index = 0; index < this->Size(); ++index) {
    fun(operator[](index));
  }
}

/* ************************************************************************** */

// Specific member functions (MutableContainer) (inherited from PostOrderMappableContainer)

template<typename Data>
inline void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
  ulong index = this->Size();
  while (index > 0) {
    fun(operator[](--index));
  }
}

/* ************************************************************************** */

// Specific member functions (SortableLinearContainer)

template<typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
  QuickSort(0, this->Size() - 1);
}

template<typename Data>
void SortableLinearContainer<Data>::QuickSort(ulong p, ulong r) noexcept {
  if (p < r) {
    ulong q = Partition(p, r);
    QuickSort(p, q);
    QuickSort(q + 1, r);
  }
}

template<typename Data>
ulong SortableLinearContainer<Data>::Partition(ulong p, ulong r) noexcept {
  Data x = this->operator[](p);
  ulong i = p - 1;
  ulong j = r + 1;
  do {
    do { j--; }
    while (x < this->operator[](j));
    do { i++; }
    while (x > this->operator[](i));
    if (i < j) { std::swap(this->operator[](i), this->operator[](j)); }
  }
  while (i < j);
  return j;
}

/* ************************************************************************** */

// Comparison operators (SortableLinearContainer)

template<typename Data>
bool SortableLinearContainer<Data>::operator==(const SortableLinearContainer<Data> & con) const noexcept {
  return LinearContainer<Data>::operator==(con);
}

template<typename Data>
inline bool SortableLinearContainer<Data>::operator!=(const SortableLinearContainer<Data> & con) const noexcept {
  return LinearContainer<Data>::operator!=(con);
}

/* ************************************************************************** */

}
