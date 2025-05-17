
// The implementations are already included inside the lasd namespace from dictionary.hpp,
// so we should not redeclare the namespace here

/* ************************************************************************** */

// Specific member functions (DictionaryContainer)

template<typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> & con) {
  bool all = true;
  con.Traverse(
    [this, &all](const Data & dat) {
      all &= Insert(dat);
    }
  );
  return all;
}

template<typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> && con) {
  bool all = true;
  con.Map(
    [this, &all](Data & dat) {
      all &= Insert(std::move(dat));
    }
  );
  return all;
}

template<typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> & con) {
  bool all = true;
  con.Traverse(
    [this, &all](const Data & dat) {
      all &= Remove(dat);
    }
  );
  return all;
}

template<typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> & con) {
  bool some = false;
  con.Traverse(
    [this, &some](const Data & dat) {
      some |= Insert(dat);
    }
  );
  return some;
}

template<typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> && con) {
  bool some = false;
  con.Map(
    [this, &some](Data & dat) {
      some |= Insert(std::move(dat));
    }
  );
  return some;
}

template<typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> & con) {
  bool some = false;
  con.Traverse(
    [this, &some](const Data & dat) {
      some |= Remove(dat);
    }
  );
  return some;
}

/* ************************************************************************** */

// Specific member functions (OrderedDictionaryContainer)

template<typename Data>
Data OrderedDictionaryContainer<Data>::MinNRemove() {
  Data dato = Min();
  this->Remove(dato);
  return dato;
}

template<typename Data>
void OrderedDictionaryContainer<Data>::RemoveMin() {
  this->Remove(Min());
}

template<typename Data>
Data OrderedDictionaryContainer<Data>::MaxNRemove() {
  Data dato = Max();
  this->Remove(dato);
  return dato;
}

template<typename Data>
void OrderedDictionaryContainer<Data>::RemoveMax() {
  this->Remove(Max());
}

template<typename Data>
Data OrderedDictionaryContainer<Data>::PredecessorNRemove(const Data & dato) {
  Data predecessore = Predecessor(dato);
  this->Remove(predecessore);
  return predecessore;
}

template<typename Data>
void OrderedDictionaryContainer<Data>::RemovePredecessor(const Data & dato) {
  this->Remove(Predecessor(dato));
}

template<typename Data>
Data OrderedDictionaryContainer<Data>::SuccessorNRemove(const Data & dato) {
  Data successore = Successor(dato);
  this->Remove(successore);
  return successore;
}

template<typename Data>
void OrderedDictionaryContainer<Data>::RemoveSuccessor(const Data & dato) {
  this->Remove(Successor(dato));
}

/* ************************************************************************** */
