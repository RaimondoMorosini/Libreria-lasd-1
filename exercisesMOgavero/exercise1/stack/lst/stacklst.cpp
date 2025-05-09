
namespace lasd {

/* ************************************************************************** */

// Copy assignment (StackLst)
template<typename Data>
inline StackLst<Data> & StackLst<Data>::operator=(const StackLst<Data> & stk) {
  List<Data>::operator=(stk);
  return *this;
}

// Move assignment (StackLst)
template<typename Data>
inline StackLst<Data> & StackLst<Data>::operator=(StackLst<Data> && stk) noexcept {
  List<Data>::operator=(std::move(stk));
  return *this;
}

/* ************************************************************************** */

// Comparison operators (StackLst)

template<typename Data>
inline bool StackLst<Data>::operator==(const StackLst<Data> & stk) const noexcept {
  return List<Data>::operator==(stk);
}

template<typename Data>
inline bool StackLst<Data>::operator!=(const StackLst<Data> & stk) const noexcept {
  return List<Data>::operator!=(stk);
}

/* ************************************************************************** */

// Specific member functions (StackLst) (inherited from Stack)

template<typename Data>
inline const Data & StackLst<Data>::Top() const {
  return List<Data>::Front();
}

template<typename Data>
inline Data & StackLst<Data>::Top() {
  return List<Data>::Front();
}

template<typename Data>
inline void StackLst<Data>::Pop() {
  return List<Data>::RemoveFromFront();
}

template<typename Data>
inline Data StackLst<Data>::TopNPop() {
  return List<Data>::FrontNRemove();
}

template<typename Data>
inline void StackLst<Data>::Push(const Data & dat) {
  return List<Data>::InsertAtFront(dat);
}

template<typename Data>
inline void StackLst<Data>::Push(Data && dat) {
  return List<Data>::InsertAtFront(dat);
}

/* ************************************************************************** */

}
