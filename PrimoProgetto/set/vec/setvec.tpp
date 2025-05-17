#ifndef SETVEC_TPP
#define SETVEC_TPP

#include <stdexcept>
#include <functional>
namespace lasd {

/* ************************************************************************ */

// Costruttore da TraversableContainer
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& con) {
  for (const auto& elem : con) {
    Insert(elem);
  }
}

// Costruttore da MappableContainer (rvalue)
template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& con) {
  con.Map(
    [this](Data&& elem) {
      Insert(std::move(elem));
    }
  );
}

// Copy constructor TODO VEDERE SE FUNZIONA
template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& other)
  : vec(other.vec), head(other.head), tail(other.tail) {
  this->size = other.size;
}


// Move constructor TODO VEDERE SE FUNZIONA
template <typename Data>
SetVec<Data>::SetVec(SetVec<Data>&& other) noexcept
  : vec(std::move(other.vec)), head(other.head), tail(other.tail) {
  size = other.size;
  other.head = other.tail = other.size = 0;
}

// Copy assignment
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other) {
  if (this != &other) {
    vec = other.vec;
    head = other.head;
    tail = other.tail;
    size = other.size;
  }
  return *this;
}

// Move assignment
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& other) noexcept {
  std::swap(vec, other.vec);
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
  return *this;
}

// Equality
template <typename Data>
inline bool SetVec<Data>::operator==(const SetVec<Data>& other) const noexcept {
  if (size != other.size)
    return false;
  for (ulong i = 0; i < size; ++i)
    if ((*this)[i] != other[i])
      return false;
  return true;
}

template <typename Data>
inline bool SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************ */

// Resize helper
template <typename Data>
void SetVec<Data>::Resize(ulong newCap) {
    //TODO: Implementare Resize
}

template <typename Data>
ulong SetVec<Data>::LowerBoundIndex(const Data& val) const {
  ulong low = 0;
  ulong high = size;

  while (low < high) {
    ulong mid = low + (high - low) / 2;
    if ((*this)[mid] < val)
      low = mid + 1;
    else
      high = mid;
  }
  return low;
}

// Operator[] non-const implementation for internal use
template <typename Data>
Data& SetVec<Data>::operator[](ulong index) {
  if (index >= size) throw std::out_of_range("Index out of bounds");
  return vec[(head + index) % vec.Size()];
}
// Inserimento ordinato
template <typename Data>
bool SetVec<Data>::Insert(const Data& val) {
  if (Exists(val)) return false;

  if (size == vec.Size())
    Resize(vec.Size() == 0 ? 1 : vec.Size() * 2);

  ulong i = 0;
  while (i < size && (*this)[i] < val)
    ++i;

  // Shift elements right from tail to i
  for (ulong j = size; j > i; --j)
    (*this)[j] = std::move((*this)[j - 1]);

  (*this)[i] = val;
  ++size;
  tail = (head + size) % vec.Size();
  return true;
}

//TODO controllare se funziona
template <typename Data>
bool SetVec<Data>::Insert(Data&& val) {
  if (Exists(val)) return false;

  if (size == vec.Size())
    Resize(vec.Size() == 0 ? 1 : vec.Size() * 2);

  ulong i = 0;
  while (i < size && (*this)[i] < val)
    ++i;

  for (ulong j = size; j > i; --j)
    (*this)[j] = std::move((*this)[j - 1]);

  (*this)[i] = std::move(val);
  ++size;
  tail = (head + size) % vec.Size();
  return true;
}

// Remove
template <typename Data>
bool SetVec<Data>::Remove(const Data& val) {
  // Find the element's index
  ulong i = 0;
  bool found = false;

  // Search for the element
  while (i < size && !found) {
    if ((*this)[i] == val) {
      found = true;
    } else {
      ++i;
    }
  }

  // If element not found, return false
  if (!found) return false;

  // Shift elements left by one position
  for (ulong j = i; j < size - 1; ++j) {
    (*this)[j] = std::move((*this)[j + 1]);
  }

  // Decrement size and update tail
  --size;
  tail = (head + size) % vec.Size();
  
  return true;
}

// operator[]
template <typename Data>
const Data& SetVec<Data>::operator[](ulong index) const {
  if (index >= size) throw std::out_of_range("Index out of bounds");
  return vec[(head + index) % vec.Size()];
}

/* ************************************************************************ */

// Exists
template <typename Data>
bool SetVec<Data>::Exists(const Data& val) const noexcept {
  if (size == 0) return false;
  
  ulong index = LowerBoundIndex(val);
  
  // Check if index is valid and the element at index equals val
  return (index < size && !(val < (*this)[index]) && !((*this)[index] < val));
}

// Clear
template <typename Data>
void SetVec<Data>::Clear() {
  vec.Clear();
  size = head = tail = 0;
}

/* ************************************************************************ */

// Min/Max/Predecessor/Successor e versioni NRemove / Remove

template <typename Data>
const Data& SetVec<Data>::Min() const {
  if (size == 0) throw std::length_error("Empty container");
  return (*this)[0];
}

template <typename Data>
Data SetVec<Data>::MinNRemove() {
  Data tmp = Min();
  RemoveMin();
  return tmp;
}

template <typename Data>
void SetVec<Data>::RemoveMin() {
  if (size == 0) throw std::length_error("Empty container");
  
  // Shift all elements one position left
  for (ulong i = 0; i < size - 1; ++i) {
    (*this)[i] = std::move((*this)[i + 1]);
  }
  
  // Update size and tail
  --size;
  tail = (head + size) % vec.Size();
}

template <typename Data>
const Data& SetVec<Data>::Max() const {
  if (size == 0) throw std::length_error("Empty container");
  return (*this)[size-1];
}

template <typename Data>
Data SetVec<Data>::MaxNRemove() {
  Data tmp = Max();
  RemoveMax();
  return tmp;
}

template <typename Data>
void SetVec<Data>::RemoveMax() {
  if (size == 0) throw std::length_error("Empty container");
  --size;
  tail = (head + size) % vec.Size();
}

/* ************************************************************************ */

// Predecessor
template <typename Data>
const Data& SetVec<Data>::Predecessor(const Data& val) const {
  if (size < 2) throw std::length_error("No predecessor");
  
  // Find lower bound index
  ulong index = LowerBoundIndex(val);
  
  // If index is 0 or val is not found, there's no predecessor
  if (index == 0 || (index < size && !((*this)[index] < val) && !(val < (*this)[index]))) {
    if (index == 0) throw std::length_error("No predecessor");
    index--;
  } else {
    // Index is already pointing to predecessor
    index--;
  }
  
  // If we reach here, index should be pointing to predecessor
  if (index >= size) throw std::length_error("Predecessor not found");
  
  return (*this)[index];
}

template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& val) {
  Data tmp = Predecessor(val);
  Remove(tmp);
  return tmp;
}

template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& val) {
  Remove(Predecessor(val));
}

// Successor
template <typename Data>
const Data& SetVec<Data>::Successor(const Data& val) const {
  if (size < 2) throw std::length_error("No successor");
  
  // Find lower bound index
  ulong index = LowerBoundIndex(val);
  
  // If val exists in the set, get the next element
  if (index < size && !((*this)[index] < val) && !(val < (*this)[index])) {
    index++;
  }
  
  // Check if successor exists
  if (index >= size) throw std::length_error("No successor");
  
  return (*this)[index];
}

template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& val) {
  Data tmp = Successor(val);
  Remove(tmp);
  return tmp;
}

template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& val) {
  Remove(Successor(val));
}

} // namespace lasd

#endif // SETVEC_TPP
