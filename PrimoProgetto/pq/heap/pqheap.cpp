#include <stdexcept>


namespace lasd {

/* ************************************************************************ */

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

/* ************************************************************************ */

// Tip
template <typename Data>
const Data& PQHeap<Data>::Tip() const {
  if (heapsize == 0) {
    throw std::length_error("Access to Tip from an empty PQHeap");
  }
  return Elements[0];
}

// RemoveTip
template <typename Data>
void PQHeap<Data>::RemoveTip() {
  if (heapsize == 0) {
    throw std::length_error("RemoveTip on an empty PQHeap");
  }
  std::swap(Elements[0], Elements[heapsize - 1]);
  heapsize--;
  HeapifyDown(0, heapsize);
}

// TipNRemove
template <typename Data>
Data PQHeap<Data>::TipNRemove() {
  if (heapsize == 0) {
    throw std::length_error("TipNRemove on an empty PQHeap");
  }
  Data tmp = std::move(Elements[0]);
  RemoveTip();
  return tmp;
}

/* ************************************************************************ */

// Insert (copy)
template <typename Data>
void PQHeap<Data>::Insert(const Data& dat) {
  if (heapsize == GetCapacity()) {
    Resize(heapsize * 2 + 1); // Espansione dinamica
  }
  Elements[heapsize] = dat;
  HeapifyUp(heapsize);
  heapsize++;
}

// Insert (move)
template <typename Data>
void PQHeap<Data>::Insert(Data&& dat) {
  if (heapsize == GetCapacity()) {
    Resize(heapsize * 2 + 1);
  }
  Elements[heapsize] = std::move(dat);
  HeapifyUp(heapsize);
  heapsize++;
}

/* ************************************************************************ */

// Change (copy)
template <typename Data>
void PQHeap<Data>::Change(const ulong index, const Data& dat) {
  if (index >= heapsize) {
    throw std::out_of_range("Index out of bounds in Change()");
  }
  if (dat < Elements[index]) {
    Elements[index] = dat;
    HeapifyUp(index);
  } else {
    Elements[index] = dat;
    HeapifyDown(index, heapsize);
  }
}

// Change (move)
template <typename Data>
void PQHeap<Data>::Change(const ulong index, Data&& dat) {
  if (index >= heapsize) {
    throw std::out_of_range("Index out of bounds in Change()");
  }
  if (dat < Elements[index]) {
    Elements[index] = std::move(dat);
    HeapifyUp(index);
  } else {
    Elements[index] = std::move(dat);
    HeapifyDown(index, heapsize);
  }
}
// * ************************************************************************ */

//function auxiliary
ulong GetCapacity() const {
    return size;
  }


/* ************************************************************************ */

} // namespace lasd