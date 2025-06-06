#include <iostream>
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& container) : Vector<Data>(container) {
  Heapify();
  std::cout << "<HeapVec constructor called from TraversableContainer>" << std::endl;
}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data>&& container)  : Vector<Data>(std::move(container)){
  Heapify();
  std::cout << "<HeapVec move constructor called from MappableContainer>" << std::endl;
}

// Copy constructor
template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data>& other)// : Vector<Data>(other)
{
  Vector<Data>::operator=(other);
  std::cout << "HeapVec copy constructor called" << std::endl;
  // No need to call Heapify here, as the copied vector is already a heap
}

// Move constructor
template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data>&& other) noexcept {
  //esplicitly call the base class move constructor
  Vector<Data>::operator=(std::move(other));
  std::cout<< "HeapVec move constructor called" << std::endl;
}

// Copy assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& other) {
  Vector<Data>::operator=(other);
  return *this;
  std::cout << "HeapVec copy assignment called" << std::endl;
}

// Move assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& other) noexcept {
  Vector<Data>::operator=(std::move(other));
  return *this;
  std::cout << "HeapVec move assignment called" << std::endl;
}

// Comparison operators
template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data>& other) const noexcept {
  return Vector<Data>::operator==(other);
}

template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data>& other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Heap operations

template <typename Data>
void HeapVec<Data>::Heapify() {
  if (this->Size() > 1) {
    for (long i = (this->Size() / 2) - 1; i >= 0; --i)
      HeapifyDown(i);
  }
}

template <typename Data>
bool HeapVec<Data>::IsHeap() const noexcept {
  for (ulong i = 0; i < this->Size() / 2; ++i) {
    ulong left = 2 * i + 1;
    ulong right = 2 * i + 2;

    if (left < this->Size() && Elements[i] < Elements[left])
      return false;
    if (right < this->Size() && Elements[i] < Elements[right])
      return false;
  }
  return true;
}

template <typename Data>
void HeapVec<Data>::HeapifyDown(ulong i) {
  ulong largest = i;
  ulong left = 2 * i + 1;
  ulong right = 2 * i + 2;

  if (left < this->Size() && Elements[left] > Elements[largest])
    largest = left;

  if (right < this->Size() && Elements[right] > Elements[largest])
    largest = right;

  if (largest != i) {
    std::swap(Elements[i], Elements[largest]);
    HeapifyDown(largest);
  }
}

template <typename Data>
void HeapVec<Data>::HeapifyUp(ulong i) {
  while (i > 0) {
    ulong parent = (i - 1) / 2;
    if (Elements[i] > Elements[parent]) {
      std::swap(Elements[i], Elements[parent]);
      i = parent;
    } else {
      break;
    }
  }
}

/* ************************************************************************** */

// Sorting using HeapSort

template <typename Data>
void HeapVec<Data>::Sort() noexcept {
  Heapify(); // Ensure max-heap

  for (ulong i = this->Size() - 1; i > 0; --i) {
    std::swap(Elements[0], Elements[i]);
    ulong tempSize = i;
    ulong root = 0;

    while (true) {
      ulong largest = root;
      ulong left = 2 * root + 1;
      ulong right = 2 * root + 2;

      if (left < tempSize && Elements[left] > Elements[largest])
        largest = left;

      if (right < tempSize && Elements[right] > Elements[largest])
        largest = right;

      if (largest != root) {
        std::swap(Elements[root], Elements[largest]);
        root = largest;
      } else {
        break;
      }
    }
  }
}

/* ************************************************************************** */

}
