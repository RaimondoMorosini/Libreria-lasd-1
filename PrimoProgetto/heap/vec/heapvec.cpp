namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& container) : Vector<Data>(container) {
  Heapify();
}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data>&& container) : Vector<Data>(std::move(container)) {
  Heapify();
}

// Copy constructor
template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data>& other) : Vector<Data>(other) {}

// Move constructor
template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data>&& other) noexcept : Vector<Data>(std::move(other)) {}

// Copy assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& other) {
  Vector<Data>::operator=(other);
  return *this;
}

// Move assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& other) noexcept {
  Vector<Data>::operator=(std::move(other));
  return *this;
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
  if (size > 1) {
    for (long i = (size / 2) - 1; i >= 0; --i)
      HeapifyDown(i);
  }
}

template <typename Data>
bool HeapVec<Data>::IsHeap() const noexcept {
  for (ulong i = 0; i < size / 2; ++i) {
    ulong left = 2 * i + 1;
    ulong right = 2 * i + 2;

    if (left < size && Elements[i] < Elements[left])
      return false;
    if (right < size && Elements[i] < Elements[right])
      return false;
  }
  return true;
}

template <typename Data>
void HeapVec<Data>::HeapifyDown(ulong i) {
  ulong largest = i;
  ulong left = 2 * i + 1;
  ulong right = 2 * i + 2;

  if (left < size && Elements[left] > Elements[largest])
    largest = left;

  if (right < size && Elements[right] > Elements[largest])
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

  for (ulong i = size - 1; i > 0; --i) {
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
