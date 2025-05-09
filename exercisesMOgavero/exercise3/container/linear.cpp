
namespace lasd {

/* ************************************************************************** */

// Comparison operators (LinearContainer)

template<typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data> & con) const noexcept {
  if (size == con.size) {
    for (ulong index = 0; index < size; ++index) {
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
inline Data & LinearContainer<Data>::Front() {
  return operator[](0);
}

template <typename Data>
inline const Data & LinearContainer<Data>::Back() const {
  return operator[](size - 1);
}

template <typename Data>
inline Data & LinearContainer<Data>::Back() {
  return operator[](size - 1);
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
  for (ulong index = 0; index < size; ++index) {
    fun(operator[](index));
  }
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PostOrderTraversableContainer)

template<typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
  ulong index = size;
  while (index > 0) {
    fun(operator[](--index));
  }
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from MappableContainer)

template<typename Data>
inline void LinearContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PreOrderMappableContainer)

template<typename Data>
inline void LinearContainer<Data>::PreOrderMap(MapFun fun) {
  for (ulong index = 0; index < size; ++index) {
    fun(operator[](index));
  }
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PostOrderMappableContainer)

template<typename Data>
inline void LinearContainer<Data>::PostOrderMap(MapFun fun) {
  ulong index = size;
  while (index > 0) {
    fun(operator[](--index));
  }
}

/* ************************************************************************** */

// Specific member functions (SortableLinearContainer)

template<typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
  QuickSort(0, size - 1);
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
