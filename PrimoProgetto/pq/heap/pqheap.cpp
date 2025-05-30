#include <stdexcept>


namespace lasd {

/* ************************************************************************** */

// Costruttore da TraversableContainer (copia)
template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& con) {
  HeapVec<Data>::operator=(HeapVec<Data>(con));  // Forza l'invocazione corretta
}

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data>&& con) {
  HeapVec<Data>::operator=(HeapVec<Data>(std::move(con)));  // Forza l'invocazione corretta
}

// Costruttore di copia
template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data>& other) : HeapVec<Data>(other) {
  // Copy costruisce già correttamente
}

// Costruttore di move
template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data>&& other) noexcept : HeapVec<Data>(std::move(other)) {
  // Move costruisce già correttamente
}


/* ************************************************************************** */

// Copy assignment
template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& other) {
  HeapVec<Data>::operator=(other);
  return *this;
}

// Move assignment
template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& other) noexcept {
  HeapVec<Data>::operator=(std::move(other));
  return *this;
}

/* ************************************************************************** */

// Tip (access root of heap)
template <typename Data>
const Data& PQHeap<Data>::Tip() const {
  if (size == 0) {
    throw std::length_error("Priority Queue is empty");
  }
  return Elements[0];
}

// RemoveTip (remove root of heap)
template <typename Data>
void PQHeap<Data>::RemoveTip() {
  if (size == 0) throw std::length_error("Heap vuoto");
  std::swap(Elements[0], Elements[size - 1]);
  Resize(size - 1);  // elimina l'ultimo
  if (size > 0)
    HeapifyDown(0);
}


// TipNRemove (return and remove root)
template <typename Data>
Data PQHeap<Data>::TipNRemove() {
    Data tmp = Tip(); // Get the root
    RemoveTip(); // Remove the root
    return tmp; // Return the removed root
}

/* ************************************************************************** */

// Insert (copy)
template <typename Data>
void PQHeap<Data>::Insert(const Data& dat) {
        Resize(size + 1); // Ensure enough space

  Elements[size-1] = dat;
  HeapifyUp(size - 1);
}

// Insert (move)
template <typename Data>
void PQHeap<Data>::Insert(Data&& dat) {
    Resize(size + 1); // Ensure enough space
  Elements[size -1] = std::move(dat);
  HeapifyUp(size - 1);
}

/* ************************************************************************** */

// Change (copy)
template <typename Data>
void PQHeap<Data>::Change(const ulong index, const Data& dat) {
  if (index >= size) {
    throw std::out_of_range("Index out of range");
  }
  Data old = Elements[index];
  Elements[index] = dat;
  if (dat < old) {
    HeapifyDown(index);
  } else {
    HeapifyUp(index);
  }
}

// Change (move)
template <typename Data>
void PQHeap<Data>::Change(const ulong index, Data&& dat) {
  if (index >= size) {
    throw std::out_of_range("Index out of range");
  }
  Data old = Elements[index];
  Elements[index] = std::move(dat);
  if (Elements[index] < old) {
    HeapifyDown(index);
  } else {
    HeapifyUp(index);
  }
}

/* ************************************************************************** */

}
