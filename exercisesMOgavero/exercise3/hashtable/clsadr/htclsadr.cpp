
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() {
  Table = new BST<Data>[tablesize] {};
}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(ulong newtablesize) {
  tablesize = newtablesize;
  Table = new BST<Data>[tablesize] {};
}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data> & con) {
  InsertAll(con);
}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(ulong newtablesize, const TraversableContainer<Data> & con) : HashTableClsAdr(newtablesize) {
  InsertAll(con);
}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data> && con) {
  InsertAll(std::move(con));
}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(ulong newtablesize, MappableContainer<Data> && con) : HashTableClsAdr(newtablesize) {
  InsertAll(std::move(con));
}

/* ************************************************************************** */

// Copy constructor
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data> & ht) : HashTable<Data>(ht) {
  Table = new BST<Data>[tablesize] {};
  std::copy(ht.Table, ht.Table + tablesize, Table);
}

// Move constructor
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data> && ht) noexcept : HashTable<Data>(std::move(ht)) {
  std::swap(Table, ht.Table);
}

/* ************************************************************************** */

// Destructor
template<typename Data>
HashTableClsAdr<Data>::~HashTableClsAdr() {
  delete[] Table;
}

/* ************************************************************************** */

// Copy assignment
template<typename Data>
HashTableClsAdr<Data> & HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data> & ht) {
  HashTableClsAdr<Data> * tmpht = new HashTableClsAdr<Data>(ht);
  std::swap(*tmpht, *this);
  delete tmpht;
  return *this;
}

// Move assignment
template<typename Data>
HashTableClsAdr<Data> & HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data> && ht) noexcept {
  HashTable<Data>::operator=(std::move(ht));
  std::swap(Table, ht.Table);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template<typename Data>
inline bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data> & ht) const noexcept {
  if (size == ht.Size()) {
    bool equal = true;
    for (ulong i = 0; i < tablesize; ++i) {
      Table[i].Traverse(
        [ht, &equal](const Data & dat) {
          equal &= ht.Exists(dat);
        }
      );
    }
    return equal;
  }
  return false;
}

template<typename Data>
inline bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data> & ht) const noexcept {
  return !(*this == ht);
}

/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

template<typename Data>
bool HashTableClsAdr<Data>::Insert(const Data & dat) {
  if (Table[HashKey(dat)].Insert(dat)) {
    ++size;
    return true;
  }
  return false;
}

template<typename Data>
bool HashTableClsAdr<Data>::Insert(Data && dat) {
  if (Table[HashKey(dat)].Insert(std::move(dat))) {
    ++size;
    return true;
  }
  return false;
}

template<typename Data>
bool HashTableClsAdr<Data>::Remove(const Data & dat) {
  if (Table[HashKey(dat)].Remove(dat)) {
    --size;
    return true;
  }
  return false;
}

/* ************************************************************************** */

// Specific member functions (inherited from TestableContainer)

template<typename Data>
bool HashTableClsAdr<Data>::Exists(const Data & dat) const noexcept {
  return Table[HashKey(dat)].Exists(dat);
};

/* ************************************************************************** */

// Specific member functions (inherited from ResizableContainer)

template<typename Data>
void HashTableClsAdr<Data>::Resize(ulong newtablesize) {
  HashTableClsAdr<Data> * tmpht = new HashTableClsAdr<Data>(newtablesize);
  for (ulong i = 0; i < tablesize; ++i) {
    Table[i].Traverse(
      [tmpht](const Data & dat) {
        tmpht->Insert(std::move(dat));
      }
    );
  }
  std::swap(*tmpht, *this);
  delete tmpht;
};

/* ************************************************************************** */

// Specific member functions (inherited from ClearableContainer)

template<typename Data>
void HashTableClsAdr<Data>::Clear() {
  size = 0;
  tablesize = 127;
  delete[] Table;
  Table = new BST<Data>[tablesize] {};
}

/* ************************************************************************** */

}
