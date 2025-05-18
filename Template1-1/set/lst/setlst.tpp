#ifndef SETLST_TPP
#define SETLST_TPP

#include <stdexcept>
#include <utility>
#include <vector>
#include <algorithm>

namespace lasd {

/* ************************************************************************ */

// Costruttore da TraversableContainer
template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data>& con) {
  std::vector<Data> tmp;
  tmp.reserve(con.Size());
  con.Traverse([&tmp](const Data& d) {
    tmp.push_back(d);
  });
  std::sort(tmp.begin(), tmp.end());
  tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
  for (const Data& d : tmp) {
    List<Data>::InsertAtBack(d);
    ++size;
  }
}

// Costruttore da MappableContainer
template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data>&& con) {
  std::vector<Data> tmp;
  tmp.reserve(con.Size());
  con.Map([&tmp](Data&& d) {
    tmp.push_back(std::move(d));
  });
  std::sort(tmp.begin(), tmp.end());
  tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
  for (Data& d : tmp) {
    List<Data>::InsertAtBack(std::move(d));
    ++size;
  }
}

// Copy constructor
template <typename Data>
SetLst<Data>::SetLst(const SetLst<Data>& other) : List<Data>(other) {}

// Move constructor
template <typename Data>
SetLst<Data>::SetLst(SetLst<Data>&& other) noexcept : List<Data>(std::move(other)) {}

// Copy assignment
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(const SetLst<Data>& other) {
  List<Data>::operator=(other);
  return *this;
}

// Move assignment
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(SetLst<Data>&& other) noexcept {
  List<Data>::operator=(std::move(other));
  return *this;
}

// Equality operator
template <typename Data>
bool SetLst<Data>::operator==(const SetLst<Data>& other) const noexcept {
  if (size != other.size) return false;
  auto n1 = head;
  auto n2 = other.head;
  while (n1 != nullptr && n2 != nullptr) {
    if (n1->lem != n2->lem) return false;
    n1 = n1->next;
    n2 = n2->next;
  }
  return true;
}

// Inequality operator
template <typename Data>
bool SetLst<Data>::operator!=(const SetLst<Data>& other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************ */

// Insert (copy)
template <typename Data>
bool SetLst<Data>::Insert(const Data& val) {
  if (Exists(val)) return false;
  auto prev = head;
  auto curr = head;
  while (curr != nullptr && curr->lem < val) {
    prev = curr;
    curr = curr->next;
  }
  if (curr == head) {
    List<Data>::InsertAtFront(val);
  } else if (curr == nullptr) {
    List<Data>::InsertAtBack(val);
  } else {
    List<Data>::InsertBefore(curr, val);
  }
  ++size;
  return true;
}

// Insert (move)
template <typename Data>
bool SetLst<Data>::Insert(Data&& val) {
  if (Exists(val)) return false;
  auto prev = head;
  auto curr = head;
  while (curr != nullptr && curr->lem < val) {
    prev = curr;
    curr = curr->next;
  }
  if (curr == head) {
    List<Data>::InsertAtFront(std::move(val));
  } else if (curr == nullptr) {
    List<Data>::InsertAtBack(std::move(val));
  } else {
    List<Data>::InsertBefore(curr, std::move(val));
  }
  ++size;
  return true;
}

// Remove
template <typename Data>
bool SetLst<Data>::Remove(const Data& val) {
  auto curr = head;
  while (curr != nullptr) {
    if (curr->lem == val) {
      List<Data>::Remove(curr);
      --size;
      return true;
    }
    curr = curr->next;
  }
  return false;
}

// Exists
template <typename Data>
bool SetLst<Data>::Exists(const Data& val) const noexcept {
  auto curr = head;
  while (curr != nullptr) {
    if (curr->lem == val) return true;
    if (val < curr->lem) return false;
    curr = curr->next;
  }
  return false;
}

// Clear
template <typename Data>
void SetLst<Data>::Clear() {
  List<Data>::Clear();
  size = 0;
}

// operator[] const
template <typename Data>
const Data& SetLst<Data>::operator[](ulong index) const {
  return List<Data>::operator[](index);
}

} // namespace lasd

#endif // SETLST_TPP
