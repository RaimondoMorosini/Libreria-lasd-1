namespace lasd {
// implementation of the Map function for PreOrderMappableContainer and PostOrderMappableContainer


template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun fun) {
  PostOrderMap(fun);
}

}
