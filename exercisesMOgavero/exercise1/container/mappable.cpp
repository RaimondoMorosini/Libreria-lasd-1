
namespace lasd {

/* ************************************************************************** */

// Specific member functions (PreOrderMappableContainer)

template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member functions (PostOrderMappableContainer)

template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun fun) {
  PostOrderMap(fun);
}

/* ************************************************************************** */

// Specific member functions (InOrderMappableContainer)

template <typename Data>
inline void InOrderMappableContainer<Data>::Map(MapFun fun) {
  InOrderMap(fun);
}

/* ************************************************************************** */

// Specific member functions (BreadthMappableContainer)

template <typename Data>
inline void BreadthMappableContainer<Data>::Map(MapFun fun) {
  BreadthMap(fun);
}

/* ************************************************************************** */

}
