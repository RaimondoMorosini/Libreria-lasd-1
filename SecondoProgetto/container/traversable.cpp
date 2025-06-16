
namespace lasd {

/* **************************************************************************
    implementation of TraversableContainer member functions  */
template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> function, Accumulator accumulator) const {
  
    // Lambda dichiarata separatamente per legibilità
  auto foldingLambda = [function, &accumulator](const Data& element) {
    accumulator = function(element, accumulator);
  };

  Traverse(foldingLambda);

  return accumulator;
}

template <typename Data>
 inline bool TraversableContainer<Data>::Exists(const Data& value) const noexcept {

  bool found = false;

  auto existsLambda = [value, &found](const Data& element) {
    if (element == value) {
      found = true;
    }
  };

  Traverse(existsLambda);

  return found;
}


/* ************************************************************************** */

// Specific member functions (PreOrderTraversableContainer)

template <typename Data>
template <typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> function, Accumulator accumulator) const {
    // Lambda dichiarata separatamente per legibilità
    auto foldingLambda = [function, &accumulator](const Data& element) {
      accumulator = function(element, accumulator);
    };
    PreOrderTraverse(foldingLambda);


    return accumulator;
}

template <typename Data>
inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun function) const {
  PreOrderTraverse(function);
}

/* ************************************************************************** */

// Specific member functions (PostOrderTraversableContainer)

template <typename Data>
template <typename Accumulator>
inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> function, Accumulator accumulator) const {
    // Lambda dichiarata separatamente per legibilità
    auto foldingLambda = [function, &accumulator](const Data& element) {
      accumulator = function(element, accumulator);
    };
    PostOrderTraverse(foldingLambda);

    return accumulator;
}

template <typename Data>
inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun function) const {
  PostOrderTraverse(function);
}


}
