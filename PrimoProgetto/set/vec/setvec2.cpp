#include "setvec.hpp"
#include <stdexcept>
#include <algorithm>

namespace lasd {

/* ************************************************************************** */

// Default constructor
template<typename Data>
SetVec<Data>::SetVec() {
  capacity = 4;
  Elements = new Data[capacity];
}

// Specific constructor (TraversableContainer)
template<typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& con) : SetVec() {
  con.Traverse([this](const Data& dat) { Insert(dat); });
}

// Specific constructor (MappableContainer)
template<typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& con) : SetVec() {
  con.Map([this](Data& dat) { Insert(std::move(dat)); });
}

/* ************************************************************************** */

// Copy constructor
template<typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& other) : Vector<Data>(other.capacity) {
  head = 0;
  size = other.size;
  for (ulong i = 0; i < size; ++i) {
    Elements[i] = other.Elements[other.RealIndex(i)];
  }
}

// Move constructor
template<typename Data>
SetVec<Data>::SetVec(SetVec<Data>&& other) noexcept : Vector<Data>(std::move(other)) {
  std::swap(head, other.head);
  std::swap(size, other.size);
}

/* ************************************************************************** */

// Copy assignment
template<typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other) {
  SetVec<Data>* tmp = new SetVec<Data>(other);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& other) noexcept {
  Vector<Data>::operator=(std::move(other));
  std::swap(head, other.head);
  std::swap(size, other.size);
  return *this;
}

/* ************************************************************************** */

// Comparison operators
template<typename Data>
bool SetVec<Data>::operator==(const SetVec<Data>& other) const noexcept {
  if (size != other.size) return false;
  for (ulong i = 0; i < size; ++i) {
    if (Elements[RealIndex(i)] != other.Elements[other.RealIndex(i)])
      return false;
  }
  return true;
}

template<typename Data>
inline bool SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Access operator
template<typename Data>
const Data& SetVec<Data>::operator[](ulong index) const {
  if (index < size) {
    return Elements[RealIndex(index)];
  } else {
    throw std::out_of_range("Access at index " + std::to_string(index) + "; set size " + std::to_string(size) + ".");
  }
}

template<typename Data>
Data& SetVec<Data>::operator[](ulong index) {
  if (index < size) {
    return Elements[RealIndex(index)];
  } else {
    throw std::out_of_range("Access at index " + std::to_string(index) + "; set size " + std::to_string(size) + ".");
  }
}

/* ************************************************************************** */

// Clear
template<typename Data>
void SetVec<Data>::Clear() {
  size = 0;
  head = 0;
}

/* ************************************************************************** */

// Insert
template<typename Data>
bool SetVec<Data>::Insert(const Data& dat) {
  ulong idx = LowerBoundIndex(dat);
  if (idx < size && Elements[RealIndex(idx)] == dat) {
    return false;
  }

  if (size == capacity) {
    Resize(capacity * 2);
  }

  ShiftRight(idx, 1);
  Elements[RealIndex(idx)] = dat;
  ++size;
  return true;
}

template<typename Data>
bool SetVec<Data>::Insert(Data&& dat) {
  ulong idx = LowerBoundIndex(dat);
  if (idx < size && Elements[RealIndex(idx)] == dat) {
    return false;
  }

  if (size == capacity) {
    Resize(capacity * 2);
  }

  ShiftRight(idx, 1);
  Elements[RealIndex(idx)] = std::move(dat);
  ++size;
  return true;
}

/* ************************************************************************** */

// Remove
template<typename Data>
bool SetVec<Data>::Remove(const Data& dat) {
  ulong idx = LowerBoundIndex(dat);
  if (idx < size && Elements[RealIndex(idx)] == dat) {
    ShiftLeft(idx + 1, 1);
    --size;
    return true;
  }
  return false;
}

/* ************************************************************************** */

// Exists
template<typename Data>
bool SetVec<Data>::Exists(const Data& dat) const noexcept {
  ulong idx = LowerBoundIndex(dat);
  return (idx < size && Elements[RealIndex(idx)] == dat);
}

/* ************************************************************************** */

// Resize
template<typename Data>
void SetVec<Data>::Resize(ulong newcap) {
  Data* tmp = new Data[newcap];
  for (ulong i = 0; i < size; ++i) {
    tmp[i] = std::move(Elements[RealIndex(i)]);
  }
  std::swap(Elements, tmp);
  capacity = newcap;
  head = 0;
  delete[] tmp;
}

/* ************************************************************************** */

// RealIndex
template<typename Data>
ulong SetVec<Data>::RealIndex(ulong index) const {
  return (head + index) % capacity;
}

/* ************************************************************************** */

// LowerBoundIndex (binary search)
template<typename Data>
ulong SetVec<Data>::LowerBoundIndex(const Data& dat) const {
  ulong left = 0, right = size;
  while (left < right) {
    ulong mid = (left + right) / 2;
    if (Elements[RealIndex(mid)] < dat) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left;
}

/* ************************************************************************** */

// ShiftRight
template<typename Data>
void SetVec<Data>::ShiftRight(ulong start, ulong count) {
  for (long i = size - 1; i >= (long)start; --i) {
    Elements[RealIndex(i + count)] = std::move(Elements[RealIndex(i)]);
  }
}

// ShiftLeft
template<typename Data>
void SetVec<Data>::ShiftLeft(ulong start, ulong count) {
  for (ulong i = start; i < size; ++i) {
    Elements[RealIndex(i - count)] = std::move(Elements[RealIndex(i)]);
  }
}

/* ************************************************************************** */

// Min
template<typename Data>
const Data& SetVec<Data>::Min() const {
  if (size == 0) throw std::length_error("Min from empty set.");
  return Elements[RealIndex(0)];
}

template<typename Data>
Data SetVec<Data>::MinNRemove() {
  Data tmp = Min();
  RemoveMin();
  return tmp;
}

template<typename Data>
void SetVec<Data>::RemoveMin() {
  if (size == 0) throw std::length_error("RemoveMin from empty set.");
  ++head;
  --size;
}

/* ************************************************************************** */

// Max
template<typename Data>
const Data& SetVec<Data>::Max() const {
  if (size == 0) throw std::length_error("Max from empty set.");
  return Elements[RealIndex(size - 1)];
}

template<typename Data>
Data SetVec<Data>::MaxNRemove() {
  Data tmp = Max();
  RemoveMax();
  return tmp;
}

template<typename Data>
void SetVec<Data>::RemoveMax() {
  if (size == 0) throw std::length_error("RemoveMax from empty set.");
  --size;
}

/* ************************************************************************** */

// Predecessor
template<typename Data>
const Data& SetVec<Data>::Predecessor(const Data& dat) const {
  ulong idx = LowerBoundIndex(dat);
  if (idx == 0) throw std::length_error("No predecessor found.");
  return Elements[RealIndex(idx - 1)];
}

template<typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& dat) {
  Data tmp = Predecessor(dat);
  Remove(tmp);
  return tmp;
}

template<typename Data>
void SetVec<Data>::RemovePredecessor(const Data& dat) {
  Remove(Predecessor(dat));
}

/* ************************************************************************** */

// Successor
template<typename Data>
const Data& SetVec<Data>::Successor(const Data& dat) const {
  ulong idx = LowerBoundIndex(dat);
  if (idx == size) throw std::length_error("No successor found.");
  if (Elements[RealIndex(idx)] == dat) ++idx;
  if (idx == size) throw std::length_error("No successor found.");
  return Elements[RealIndex(idx)];
}

template<typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& dat) {
  Data tmp = Successor(dat);
  Remove(tmp);
  return tmp;
}

template<typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& dat) {
  Remove(Successor(dat));
}

/* ************************************************************************** */

} // namespace lasd
