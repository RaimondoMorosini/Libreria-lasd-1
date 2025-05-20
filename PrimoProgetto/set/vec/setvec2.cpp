#include "setvec.hpp"
#include <stdexcept>
#include <utility>

namespace lasd {

/* Default constructor */
template <typename Data>
SetVec<Data>::SetVec() : Vector<Data>(10), head(0), tail(0), size(0), capacity(this->Vector<Data>::size) {}

/* Specific constructors */
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& container) : Vector<Data>(container), head(0), tail(this->Vector<Data>::size), size(this->Vector<Data>::size), capacity(this->Vector<Data>::size) {}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& container) : Vector<Data>(std::move(container)), head(0), tail(this->Vector<Data>::size), size(this->Vector<Data>::size), capacity(this->Vector<Data>::size) {}

/* Copy constructor */
template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& other) : Vector<Data>(other), head(other.head), tail(other.tail), size(other.size), capacity(this->Vector<Data>::size) {}

/* Move constructor */
template <typename Data>
SetVec<Data>::SetVec(SetVec<Data>&& other) noexcept
    : Vector<Data>(std::move(other)), head(other.head), tail(other.tail), size(other.size), capacity(this->Vector<Data>::size) {
  other.head = 0;
  other.tail = 0;
  other.size = 0;
}

/* Copy assignment */
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other) {
  if (this != &other) {
    Vector<Data>::operator=(other);
    head = other.head;
    tail = other.tail;
    size = other.size;
    // capacity è alias, aggiornata automaticamente
  }
  return *this;
}

/* Move assignment */
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& other) noexcept {
  if (this != &other) {
    Vector<Data>::operator=(std::move(other));
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = 0;
    other.tail = 0;
    other.size = 0;
  }
  return *this;
}

/* Comparison operators */
template <typename Data>
bool SetVec<Data>::operator==(const SetVec<Data>& other) const noexcept {
  if (size != other.size)
    return false;

  for (ulong i = 0; i < size; i++) {
    if ((*this)[i] != other[i])
      return false;
  }
  return true;
}

template <typename Data>
bool SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
  return !(*this == other);
}

/* Access operators */
template <typename Data>
const Data& SetVec<Data>::operator[](ulong index) const {
  if (index >= size || index < 0)
    throw std::out_of_range("SetVec::operator[] const out_of_range");
  return Elements[RealIndex(index)];
}

template <typename Data>
Data& SetVec<Data>::operator[](ulong index) {
  if (index >= size || index < 0)
    throw std::out_of_range("SetVec::operator[] out_of_range");
  return Elements[RealIndex(index)];
}

/* Exists */
template <typename Data>
bool SetVec<Data>::Exists(const Data& val) const noexcept {
  ulong pos = LowerBoundIndex(val);
  return (pos < size && (*this)[pos] == val);
}

/* Clear */
template <typename Data>
void SetVec<Data>::Clear() {
  head = 0;
  tail = 0;
  size = 0;
  Vector<Data>::Clear();
}

/* Resize */
template <typename Data>
void SetVec<Data>::Resize(ulong newCapacity) {
  if (newCapacity <= size)
    return;

  Vector<Data>::Resize(newCapacity);

  // Rearrange elements to linear order in Elements buffer
  if (size == 0) {
    head = 0;
    tail = 0;
    return;
  }

  Data* newElements = new Data[newCapacity];

  for (ulong i = 0; i < size; i++) {
    newElements[i] = std::move(Elements[RealIndex(i)]);
  }

  delete[] Elements;
  Elements = newElements;
  head = 0;
  tail = size;
  capacity = newCapacity;
}

/* LowerBoundIndex - binary search */
template <typename Data>
ulong SetVec<Data>::LowerBoundIndex(const Data& val) const {
  if (size == 0)
    return 0;

  ulong left = 0;
  ulong right = size;

  while (left < right) {
    ulong mid = left + (right - left) / 2;
    if ((*this)[mid] < val)
      left = mid + 1;
    else
      right = mid;
  }
  return left;
}

/* ShiftLeft */
template <typename Data>
void SetVec<Data>::ShiftLeft(ulong start, ulong end) {
  if (start >= end) return;

  for (ulong i = start; i < end; i++) {
    Elements[RealIndex(i)] = std::move(Elements[RealIndex(i + 1)]);
  }
  tail = (tail + capacity - 1) % capacity;
  --size;
}

/* ShiftRight */
template <typename Data>
void SetVec<Data>::ShiftRight(ulong start, ulong end) {
  if (start >= end) return;

  for (ulong i = end + 1; i > start; i--) {
    Elements[RealIndex(i)] = std::move(Elements[RealIndex(i - 1)]);
  }
  tail = (tail + 1) % capacity;
  ++size;
}

/* RealIndex */
template <typename Data>
ulong SetVec<Data>::RealIndex(ulong logicalIndex) const {
  return (head + logicalIndex) % capacity;
}

/* Insert (copy) */
template <typename Data>
bool SetVec<Data>::Insert(const Data& val) {
  ulong pos = LowerBoundIndex(val);
  if (pos < size && (*this)[pos] == val)
    return false; // already exists

  if (size == capacity)
    Resize(capacity * 2);

  if (pos == size) {
    Elements[tail] = val;
    tail = (tail + 1) % capacity;
    ++size;
  }
  else {
    ShiftRight(pos, size - 1);
    Elements[RealIndex(pos)] = val;
  }

  return true;
}

/* Insert (move) */
template <typename Data>
bool SetVec<Data>::Insert(Data&& val) {
  ulong pos = LowerBoundIndex(val);
  if (pos < size && (*this)[pos] == val)
    return false; // already exists

  if (size == capacity)
    Resize(capacity * 2);

  if (pos == size) {
    Elements[tail] = std::move(val);
    tail = (tail + 1) % capacity;
    ++size;
  }
  else {
    ShiftRight(pos, size - 1);
    Elements[RealIndex(pos)] = std::move(val);
  }

  return true;
}

/* Remove */
template <typename Data>
bool SetVec<Data>::Remove(const Data& val) {
  if (size == 0)
    return false;

  ulong pos = LowerBoundIndex(val);
  if (pos == size || (*this)[pos] != val)
    return false;

  ShiftLeft(pos, size - 1);
  return true;
}

/* Min */
template <typename Data>
const Data& SetVec<Data>::Min() const {
  if (size == 0)
    throw std::length_error("SetVec::Min on empty set");
  return (*this)[0];
}

/* MinNRemove */
template <typename Data>
Data SetVec<Data>::MinNRemove() {
  if (size == 0)
    throw std::length_error("SetVec::MinNRemove on empty set");
  Data minVal = std::move((*this)[0]);
  RemoveMin();
  return minVal;
}

/* RemoveMin */
template <typename Data>
void SetVec<Data>::RemoveMin() {
  if (size == 0)
    throw std::length_error("SetVec::RemoveMin on empty set");
  ShiftLeft(0, size - 1);
}

/* Max */
template <typename Data>
const Data& SetVec<Data>::Max() const {
  if (size == 0)
    throw std::length_error("SetVec::Max on empty set");
  return (*this)[size - 1];
}

/* MaxNRemove */
template <typename Data>
Data SetVec<Data>::MaxNRemove() {
  if (size == 0)
    throw std::length_error("SetVec::MaxNRemove on empty set");
  Data maxVal = std::move((*this)[size - 1]);
  RemoveMax();
  return maxVal;
}

/* RemoveMax */
template <typename Data>
void SetVec<Data>::RemoveMax() {
  if (size == 0)
    throw std::length_error("SetVec::RemoveMax on empty set");
  tail = (tail + capacity - 1) % capacity;
  --size;
}

/* Predecessor */
template <typename Data>
const Data& SetVec<Data>::Predecessor(const Data& val) const {
  if (size == 0)
    throw std::length_error("SetVec::Predecessor on empty set");

  ulong pos = LowerBoundIndex(val);
  if (pos == 0 || (pos == size || (*this)[pos] != val))
    throw std::length_error("SetVec::Predecessor not found");

  return (*this)[pos - 1];
}

/* PredecessorNRemove */
template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& val) {
  const Data& pred = Predecessor(val);
  Data predVal = std::move(pred);
  RemovePredecessor(val);
  return predVal;
}

/* RemovePredecessor */
template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& val) {
  if (size == 0)
    throw std::length_error("SetVec::RemovePredecessor on empty set");

  ulong pos = LowerBoundIndex(val);
  if (pos == 0 || (pos == size || (*this)[pos] != val))
    throw std::length_error("SetVec::RemovePredecessor not found");

  ShiftLeft(pos - 1, size - 1);
}

/* Successor */
template <typename Data>
const Data& SetVec<Data>::Successor(const Data& val) const {
  if (size == 0)
    throw std::length_error("SetVec::Successor on empty set");

  ulong pos = LowerBoundIndex(val);
  if (pos == size || (*this)[pos] != val || pos + 1 >= size)
    throw std::length_error("SetVec::Successor not found");

  return (*this)[pos + 1];
}

/* SuccessorNRemove */
template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& val) {
  const Data& succ = Successor(val);
  Data succVal = std::move(succ);
  RemoveSuccessor(val);
  return succVal;
}

/* RemoveSuccessor */
template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& val) {
  if (size == 0)
    throw std::length_error("SetVec::RemoveSuccessor on empty set");

  ulong pos = LowerBoundIndex(val);
  if (pos == size || (*this)[pos] != val || pos + 1 >= size)
    throw std::length_error("SetVec::RemoveSuccessor not found");

  ShiftLeft(pos + 1, size - 1);
}

} // namespace lasd
