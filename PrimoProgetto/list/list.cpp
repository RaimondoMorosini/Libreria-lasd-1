
#include <stdexcept>

namespace lasd {

/* ************************************************************************** */
/* Node Member Functions */

template <typename Data>
bool List<Data>::Node::operator==(const Node& other) const noexcept {
  return (element == other.element) && 
         ((next == nullptr && other.next == nullptr) || 
          (next != nullptr && other.next != nullptr && *next == *(other.next)));
}

template <typename Data>
inline bool List<Data>::Node::operator!=(const Node& other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */
/* Constructors and Destructor */

template <typename Data>
List<Data>::List(const TraversableContainer<Data>& container) {
  container.Traverse([this](const Data& dat) { InsertAtBack(dat); });
}

template <typename Data>
List<Data>::List(MappableContainer<Data>&& container) {
  container.Map([this](Data& dat) { InsertAtBack(std::move(dat)); });
}

template <typename Data>
List<Data>::List(const List& other) {
  Node* temp = other.head;
  while (temp != nullptr) {
    InsertAtBack(temp->element);
    temp = temp->next;
  }
}

template <typename Data>
List<Data>::List(List&& other) noexcept {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
}

template <typename Data>
List<Data>::~List() {
  Clear();
}

/* ************************************************************************** */
/* Assignment Operators */

template <typename Data>
List<Data>& List<Data>::operator=(const List& other) {
  if (this != &other) {
    Clear();
    Node* temp = other.head;
    while (temp != nullptr) {
      InsertAtBack(temp->element);
      temp = temp->next;
    }
  }
  return *this;
}

template <typename Data>
List<Data>& List<Data>::operator=(List&& other) noexcept {
  if (this != &other) {
    Clear();
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
  }
  return *this;
}

/* ************************************************************************** */
/* Comparison Operators */

template <typename Data>
inline bool List<Data>::operator==(const List& other) const noexcept {
  Node* temp1 = head;
  Node* temp2 = other.head;
  while (temp1 && temp2) {
    if (temp1->element != temp2->element) return false;
    temp1 = temp1->next;
    temp2 = temp2->next;
  }
  return temp1 == nullptr && temp2 == nullptr;
}

template <typename Data>
inline bool List<Data>::operator!=(const List& other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */
/* Specific Functions */

template <typename Data>
void List<Data>::InsertAtFront(const Data& dat) {
  Node* newNode = new Node(dat);
  newNode->next = head;
  head = newNode;
  if (size == 0) tail = newNode;
  size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& dat) {
  Node* newNode = new Node(std::move(dat));
  newNode->next = head;
  head = newNode;
  if (size == 0) tail = newNode;
  size++;
}

template <typename Data>
void List<Data>::RemoveFromFront() {
  if (size == 0) throw std::length_error("List is empty");
  Node* tmp = head;
  head = head->next;
  tmp->next = nullptr;
  delete tmp;
  if (--size == 0) tail = nullptr;
}

template <typename Data>
Data List<Data>::FrontNRemove() {
  if (size == 0) throw std::length_error("List is empty");
  Data ret = std::move(head->element);
  RemoveFromFront();
  return ret;
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& dat) {
  Node* newNode = new Node(dat);
  if (tail) tail->next = newNode;
  else head = newNode;
  tail = newNode;
  size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& dat) {
  Node* newNode = new Node(std::move(dat));
  if (tail) tail->next = newNode;
  else head = newNode;
  tail = newNode;
  size++;
}

template <typename Data>
void List<Data>::RemoveFromBack() {
  if (size == 0) throw std::length_error("List is empty");
  if (size == 1) {
    delete head;
    head = tail = nullptr;
  } else {
    Node* temp = head;
    while (temp->next != tail) temp = temp->next;
    delete tail;
    tail = temp;
    tail->next = nullptr;
  }
  size--;
}

template <typename Data>
Data List<Data>::BackNRemove() {
  if (size == 0) throw std::length_error("List is empty");
  Data ret = Back();
  RemoveFromBack();
  return ret;
}

/* ************************************************************************** */
/* Access Operators and Front/Back */

template <typename Data>
Data& List<Data>::operator[](const ulong index) {
  if (index >= size) throw std::out_of_range("Index out of range");
  Node* tmp = head;
  for (ulong i = 0; i < index; i++) tmp = tmp->next;
  return tmp->element;
}

template <typename Data>
const Data& List<Data>::operator[](const ulong index) const {
  if (index >= size) throw std::out_of_range("Index out of range");
  Node* tmp = head;
  for (ulong i = 0; i < index; i++) tmp = tmp->next;
  return tmp->element;
}

template <typename Data>
Data& List<Data>::Front() {
  if (size == 0) throw std::length_error("List is empty");
  return head->element;
}

template <typename Data>
const Data& List<Data>::Front() const {
  if (size == 0) throw std::length_error("List is empty");
  return head->element;
}

template <typename Data>
Data& List<Data>::Back() {
  if (size == 0) throw std::length_error("List is empty");
  return tail->element;
}

template <typename Data>
const Data& List<Data>::Back() const {
  if (size == 0) throw std::length_error("List is empty");
  return tail->element;
}

/* ************************************************************************** */
/* Map & Traverse */

template <typename Data>
void List<Data>::Map(MapFun func) {
  Node* tmp = head;
  while (tmp != nullptr) {
    func(tmp->element);
    tmp = tmp->next;
  }
}

template <typename Data>
void List<Data>::PreOrderMap(MapFun func) {
  Map(func);
}

template <typename Data>
void List<Data>::PostOrderMap(MapFun func) {
  // Reverse map using recursion
  std::function<void(Node*)> recurse = [&](Node* node) {
    if (node) {
      recurse(node->next);
      func(node->element);
    }
  };
  recurse(head);
}

template <typename Data>
void List<Data>::Traverse(TraverseFun func) const {
  Node* tmp = head;
  while (tmp != nullptr) {
    func(tmp->element);
    tmp = tmp->next;
  }
}

template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun func) const {
  Traverse(func);
}

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun func) const {
  std::function<void(Node*)> recurse = [&](Node* node) {
    if (node) {
      recurse(node->next);
      func(node->element);
    }
  };
  recurse(head);
}

/* ************************************************************************** */
/* Clear Function */

template <typename Data>
void List<Data>::Clear() {
  delete head;
  head = tail = nullptr;
  size = 0;
}

/* ************************************************************************** */

} // namespace lasd
