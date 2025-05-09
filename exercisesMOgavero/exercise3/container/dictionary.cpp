
namespace lasd {

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

}
