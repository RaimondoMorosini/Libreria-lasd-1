
namespace lasd {

/* ************************************************************************** */

// Specific constructors (QueueVec)

template<typename Data>
QueueVec<Data>::QueueVec(const TraversableContainer<Data> & con) : Vector<Data>(con), tail(size) {
  Vector<Data>::Resize(size * 2);
}

template<typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data> && con) : Vector<Data>(std::move(con)), tail(size) {
  Vector<Data>::Resize(size * 2);
}

/* ************************************************************************** */

// Move constructor (QueueVec)
template<typename Data>
QueueVec<Data>::QueueVec(QueueVec && que) noexcept : Vector<Data>(std::move(que)) {
  std::swap(head, que.head);
  std::swap(tail, que.tail);
};

/* ************************************************************************** */

// Copy assignment (QueueVec)
template<typename Data>
QueueVec<Data> & QueueVec<Data>::operator=(const QueueVec<Data> & que) {
  Vector<Data>::operator=(que);
  head = que.head;
  tail = que.tail;
  return *this;
}

// Move assignment (QueueVec)
template<typename Data>
QueueVec<Data> & QueueVec<Data>::operator=(QueueVec<Data> && que) noexcept {
  Vector<Data>::operator=(std::move(que));
  std::swap(head, que.head);
  std::swap(tail, que.tail);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (QueueVec)

template<typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data> & que) const noexcept {
  if (Size() == que.Size()) {
    for (ulong idx1 = head, idx2 = que.head; idx1 < tail; ++idx1 %= size, ++idx2 %= que.size) {
      if (Elements[idx1] != que.Elements[idx2]) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}

template<typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data> & que) const noexcept {
  return !(*this == que);
}

/* ************************************************************************** */

// Specific member functions (QueueVec) (inherited from Queue)

template<typename Data>
const Data & QueueVec<Data>::Head() const {
  if (head != tail) {
    return Elements[head];
  } else {
    throw std::length_error("Access to an empty queue.");
  }
}

template<typename Data>
Data & QueueVec<Data>::Head() {
  if (head != tail) {
    return Elements[head];
  } else {
    throw std::length_error("Access to an empty queue.");
  }
}

template<typename Data>
void QueueVec<Data>::Dequeue() {
  if (head != tail) {
    Reduce();
    ++head %= size;
  } else {
    throw std::length_error("Access to an empty queue.");
  }
}

template<typename Data>
Data QueueVec<Data>::HeadNDequeue() {
  if (head != tail) {
    Reduce();
    Data dat(std::move(Elements[head]));
    ++head %= size;
    return dat;
  } else {
    throw std::length_error("Access to an empty queue.");
  }
}

template<typename Data>
void QueueVec<Data>::Enqueue(const Data & dat) {
  Expand();
  Elements[tail++] = dat;
  tail %= size;
}

template<typename Data>
void QueueVec<Data>::Enqueue(Data && dat) {
  Expand();
  Elements[tail++] = std::move(dat);
  tail %= size;
}

/* ************************************************************************** */

// Specific member functions (QueueVec) (inherited from Container)

template<typename Data>
inline bool QueueVec<Data>::Empty() const noexcept {
  return (head == tail);
}

template<typename Data>
inline ulong QueueVec<Data>::Size() const noexcept {
  return (((size + tail) - head) % size);
}

/* ************************************************************************** */

// Specific member functions (QueueVec) (inherited from ClearableContainer)

template<typename Data>
void QueueVec<Data>::Clear() {
  head = tail = 0;
  Vector<Data>::Resize(4);
}

/* ************************************************************************** */

// Auxiliary member functions (QueueVec)

template<typename Data>
void QueueVec<Data>::Expand() {
  ulong num = Size();
  if (num + 1 == size) {
    Resize(size * 2, num);
  }
}

template<typename Data>
void QueueVec<Data>::Reduce() {
  ulong num = Size();
  if (num + 1 == size / 4) {
    Resize(size / 2, num);
  }
}

template<typename Data>
void QueueVec<Data>::Resize(ulong newsize, ulong num) {
  Data * TmpElements = new Data[newsize];
  ulong max = (num <= newsize) ? num : newsize;
  for (ulong idx1 = head, idx2 = 0; idx2 < max; ++idx1 %= size, ++idx2) {
    std::swap(Elements[idx1], TmpElements[idx2]);
  }
  std::swap(Elements, TmpElements);
  delete[] TmpElements;
  head = 0;
  tail = num;
  size = newsize;
}

/* ************************************************************************** */

}
